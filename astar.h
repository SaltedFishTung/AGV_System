#ifndef ASTAR_H
#define ASTAR_H

#include <list>
#include <vector>
#include "graph.h"
#include "timewindowtable.h"
using namespace std;

class Node {
public:
    Node() { }
    Node(int id) : id(id) {
        F = G = H = 0;
        parent = nullptr;
        passCount = 0;
    }
    int id;
    int F;
    int G;
    int H;              // F=G+H
    int passCount;
    Node *parent;
};

class Astar {
public:
    void addPath(TimeWindowTable* twTablePtr, const Graph& G, int startId, int endId);
private:
    list<Node*> openList;
    list<Node*> closeList;

    Node* findPath(TimeWindowTable* twTablePtr, const Graph& G,
                    Node &startNode, Node &endNode);
    vector<Node *> getSurroundNodes(TimeWindowTable* twTablePtr, const Graph& G,
                                           const Node *node) const;
    Node* isInOpenList(const list<Node *> &list, const Node *node) const; //判断开启列表中是否包含某点
    Node* isInCloseList(const list<Node *> &list, const Node *node) const; //判断开启列表中是否包含某点
    Node* getLeastFNode(); //从开启列表中返回F值最小的节点
    //计算FGH值
    int calcG(const Graph& G, Node *temp_start, Node *node);
    int calcH(const Graph& G, Node *node, Node *end);
    int calcF(Node *node);
};

#endif // ASTAR_H
