#include "timewindowtable.h"
#include <time.h>
#include <math.h>
#include <limits>

TimeWindowTable::TimeWindowTable(int carNum, int edgeNum) {
    for(int i = 0; i < carNum; i++)
        _carAxis.push_back(TimeWindowsByCar(TimeWindow(0.0, 0.0, i+1, 0)));
    for(int i = 0; i < edgeNum+1; i++)
        _edgeAxis.push_back(TimeWindowsByEdge(TimeWindow(0.0, 0.0, 0, i+1)));
}

void TimeWindowTable::setTable(int carNum, int edgeNum) {
    for(int i = 0; i < carNum; i++)
        _carAxis.push_back(TimeWindowsByCar(TimeWindow(0.0, 0.0, i+1, 0)));
    for(int i = 0; i < edgeNum+1; i++)
        _edgeAxis.push_back(TimeWindowsByEdge(TimeWindow(0.0, 0.0, 0, i)));
}

void TimeWindowTable::addPath(const TimeWindow& tw, TimeWindowsByEdge::iterator insertIter) {
    _carAxis[tw.getCarID()].push_back(tw);
    _edgeAxis[tw.getEdgeID()].insert(insertIter, tw);
}

float TimeWindowTable::addPathInfo(int carIndex, const vector<int>& pathInfo, const Graph& G, int count) {
    currCarId = carIndex;
    if(pathInfo.empty()) {
        _carAxis[carIndex].push_back(
            TimeWindow(_carAxis[carIndex].back().getExitTime(), numeric_limits<float>::max(), carIndex, -1));
        return numeric_limits<float>::max();
    }
//    cout << "int: ";
//    for(int node : pathInfo)
//        cout << node << "  ";
//    cout << endl;
    try {
        if(count > 6)
            return numeric_limits<float>::max();
        if(this->_carAxis.size() > 100)
            return numeric_limits<float>::max();
        auto iter = pathInfo.begin();
        while(true) {
            int s = *iter;
            int e = *(++iter);
//            if(iter != pathInfo.begin()+1)
//                G.resume();
            if(iter == pathInfo.end())
                break;
            int edgeIndex = G.getEdgeId(s, e);
            int edgeLen = G.getShortestDist(s, e);
            TimeWindow tw(_carAxis[carIndex].back().getExitTime(),
                          _carAxis[carIndex].back().getExitTime() + edgeLen/1.0);
            tw.setDirection(s < e);
            tw.setCarID(carIndex);
            tw.setEdgeID(edgeIndex);
            TimeWindowsByEdge::iterator indexIter = isCollision(edgeIndex, tw);
//            if(indexIter == _edgeAxis[edgeIndex].begin()) {
//                Graph A(G, s, e);
//                if(A.isAlone(s)) {  // s点已经完全孤立时，回溯
//                    // 获取到达s点的路径
//                    int edgeToS = _carAxis[carIndex].back().getEdgeID();
//                    int beforeS = A.getBeforeS(s, edgeToS);

//                    //删除这辆车在edgeToS路径上对应的时间窗
//                    TimeWindow findTw = _carAxis[carIndex].back();
//                    _carAxis[carIndex].pop_back();
//                    TimeWindowsByEdge::iterator edgeAxisIter = _edgeAxis[edgeToS].begin();
//                    while(++edgeAxisIter != _edgeAxis[edgeToS].end()) {
//                        if(findTw == *edgeAxisIter) {
//                            _edgeAxis[edgeToS].erase(edgeAxisIter);
//                            break;
//                        }
//                    }
//                    A.resume();
//                    Graph B(A, beforeS, s);
//                    B.run();
//                    vector<int> newPathInfo(B.getPathInfo(beforeS, e));
//                    addPathInfo(carIndex, newPathInfo, B, count+1);
//                } else {
//                    A.run();
//                    vector<int> newPathInfo(A.getPathInfo(s, e));
//                    addPathInfo(carIndex, newPathInfo, A, count+1);
//                }
//            }
//            else {
                _carAxis[carIndex].push_back(tw);
                _edgeAxis[edgeIndex].insert(indexIter, tw);
//            }
        }
        return _carAxis[carIndex].back().getExitTime();
    } catch(const char* error) {
        //cout << error << endl;
        return numeric_limits<float>::max();
    }
}

TimeWindowsByEdge::iterator TimeWindowTable::isCollision(int edgeIndex, const TimeWindow& tw) {
    return _edgeAxis[edgeIndex].canEnter(tw);
}

void TimeWindowTable::clear() {
    int carNum = _carAxis.size();
    int edgeNum = _edgeAxis.size();
    vector<TimeWindowsByCar>().swap(_carAxis);
    vector<TimeWindowsByEdge>().swap(_edgeAxis);
    for(int i = 0; i < carNum; i++)
        _carAxis.push_back(TimeWindowsByCar(TimeWindow(0.0, 0.0, i+1, 0)));
    for(int i = 0; i < edgeNum+1; i++)
        _edgeAxis.push_back(TimeWindowsByEdge(TimeWindow(0.0, 0.0, 0, i+1)));
}

void TimeWindowTable::clearFromIndex() {
//    for(int i = 0; i < _carAxis.size(); i++) {
//        TimeWindowsByCar::iterator iter1 = _carAxis[i].begin();
//        for(int j = 0; j <= pointsIndex[tasksIndex[i]]; j++)
//            ++iter1;
//        while (iter1 != _carAxis[i].end()) {
//            TimeWindowsByEdge::iterator iter2 = _edgeAxis[iter1->getEdgeID()].begin();
//            while (++iter2 != _edgeAxis[iter1->getEdgeID()].end()) {
//                if(*iter1 == *iter2) {
//                    iter2 = _edgeAxis[iter1->getEdgeID()].erase(iter2);
//                    break;
//                }
//            }
//            iter1 = _carAxis[i].erase(iter1);
//        }
//    }
}

void TimeWindowTable::setTasksIndex(const vector<int> &ivec) {
    if(tasksIndex.empty())
        tasksIndex = ivec;
    else {
        for(unsigned i = 0; i < tasksIndex.size(); i++)
            tasksIndex[i] = min(tasksIndex[i], ivec[i]);
    }
}

ostream& operator<<(ostream& out, TimeWindowTable& table) {
    out << "car timewindow---------" << endl;
    for(unsigned i = 0; i < table._carAxis.size(); i++)
        out << table._carAxis[i] << endl;
    out << "edge timewindow--------" << endl;
    for(unsigned i = 0; i < table._edgeAxis.size(); i++)
        out << table._edgeAxis[i] << endl;
    return out;
}
