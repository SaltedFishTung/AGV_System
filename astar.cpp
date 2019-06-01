#include "astar.h"

void Astar::addPath(TimeWindowTable *twTablePtr, const Graph &G, int startId, int endId) {
    vector<int> shortestPath = G.getPathInfo(startId, endId);
    int newStartId;
    list<int> path;
    bool flag = true;
    for(unsigned i = 0; i < shortestPath.size()-1; i++) {
        int carId = twTablePtr->currCarId;
        int edgeId = G.getEdgeId(shortestPath[i], shortestPath[i+1]);
        float enterTime = twTablePtr->getCarTimeWindow(carId).back().getExitTime();
        float exitTime = enterTime + G.getShortestDist(shortestPath[i], shortestPath[i+1])/1.0;
        TimeWindow tw(enterTime, exitTime, carId, edgeId);
        tw.setDirection(shortestPath[i] < shortestPath[i+1]);
        tw.setCarID(carId);
        tw.setEdgeID(edgeId);
        TimeWindowsByEdge::iterator insertIter = twTablePtr->isCollision(edgeId, tw);
        if(insertIter != twTablePtr->getEdgeTimeWindow(edgeId).begin())
            twTablePtr->addPath(tw, insertIter);
        else {
            newStartId = shortestPath[i];
            flag = false;
            break;
        }
    }
    if(flag)
        return ;
    Node startNode(newStartId), endNode(endId);
    Node* result = findPath(twTablePtr, G, startNode, endNode);
    while (result) {
        path.push_front(result->id);
        result = result->parent;
    }
    openList.clear();
    closeList.clear();
//    cout << "out: ";
//    for(int node : path)
//        cout << node << "  ";
//    cout << endl;
    twTablePtr->addPathInfo(twTablePtr->currCarId, vector<int>(path.begin(), path.end()),
                            G, 1);
}

int Astar::calcG(const Graph &G, Node *temp_start, Node *node) {
    int extraG = G.getShortestDist(temp_start->id, node->id);
    int parentG = node->parent == nullptr ? 0 : node->parent->G;
    return parentG + extraG;
}

int Astar::calcH(const Graph &G, Node *node, Node *end) {
    return G.getShortestDist(node->id, end->id);
}

int Astar::calcF(Node *node) {
    return node->G + node->H;
}

Node* Astar::getLeastFNode() {
    if(!openList.empty()) {
        auto resNode = openList.front();
        for(auto &node : openList) {
            if(node->F < resNode->F)
                resNode = node;
        }
        return resNode;
    }
    return nullptr;
}


Node *Astar::findPath(TimeWindowTable* twTablePtr, const Graph &G, Node &startNode, Node &endNode) {
    openList.push_back(new Node(startNode.id)); //置入起点,拷贝开辟一个节点，内外隔离
    //cout << endl;
    while (!openList.empty()) {
        auto curNode = getLeastFNode(); //找到F值最小的点
        openList.remove(curNode); //从开启列表中删除
        bool isInClose = false;
        for(auto &closeNode : closeList) {
            if(closeNode->id == curNode->id)
                isInClose = true;
        }
        if(!isInClose)
            closeList.push_back(curNode); //放到关闭列表
        //cout << curNode->id;
        // 找到当前周围可以通过的路段
        auto surroundNodes = getSurroundNodes(twTablePtr, G, curNode);
        //cout << "-";
        for (auto &target : surroundNodes) {
            // 对某一节点，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
            if (!isInOpenList(openList, target)) {
                target->parent = curNode;
                target->G = calcG(G, curNode, target);
                target->H = calcH(G, target, &endNode);
                target->F = calcF(target);
                openList.push_back(target);
            }
            // 对某一个节点，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
            else {
                int tempG = calcG(G, curNode, target);
                if (tempG < target->G) {
                    target->parent = curNode;
                    target->G = tempG;
                    target->F = calcF(target);
                }
            }
            Node *resNode = isInOpenList(openList, &endNode);
            if (resNode != nullptr) {
                return resNode; //返回列表里的节点指针，不要用原来传入的endNode指针，因为发生了深拷贝
            }
        }
    }
    return nullptr;
}

Node *Astar::isInOpenList(const list<Node *> &list, const Node *node) const {
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较节点编号
    for (auto p : list) {
        if(p->id == node->id)
            return p;
    }
    return nullptr;
}

Node *Astar::isInCloseList(const list<Node *> &list, const Node *node) const {
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较节点编号
    for (auto p : list) {
        if(p->id == node->id)
            return (++(p->passCount) > 10) ? p : nullptr;
    }
    return nullptr;
}

vector<Node *> Astar::getSurroundNodes(
        TimeWindowTable* twTablePtr, const Graph& G, const Node *node) const {
    vector<Node *> surroundNodes;
    for(int id = 0; id < G.getVerNum(); id++) {
        //cout << node->id << "  " << id << endl;
        if(id != node->id && G.isAdjacent(node->id, id)) {
            int carId = twTablePtr->currCarId;
            int edgeId = G.getEdgeId(node->id, id);
            float enterTime = twTablePtr->getCarTimeWindow(carId).back().getExitTime();
            float exitTime = enterTime + G.getShortestDist(node->id, id)/1.0;
            TimeWindow tw(enterTime, exitTime, carId, edgeId);
            if(twTablePtr->isPass(edgeId, tw) && isInCloseList(closeList, new Node(id)) == nullptr)
                surroundNodes.push_back(new Node(id));
        }
    }
    return surroundNodes;
}
