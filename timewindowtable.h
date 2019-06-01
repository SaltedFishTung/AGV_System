#ifndef TIMEWINDOWTABLE_H
#define TIMEWINDOWTABLE_H

#define MAX_CAR 10
#define MAX_TASK 50

#include <vector>
#include <iostream>
#include "graph.h"
#include "timewindow.h"
#include "timewindowsbycar.h"
#include "timewindowsbyedge.h"
using namespace std;

class TimeWindowTable {
public:
    friend ostream& operator<<(ostream& out, TimeWindowTable& table);

    int currCarId;
    int currEdgeId;

    TimeWindowTable() { }
    TimeWindowTable(int carNum, int edgeNum);
    TimeWindowTable& operator=(const TimeWindowTable& table) {
        _carAxis = table._carAxis;
        _edgeAxis = table._edgeAxis;
        return *this;
    }
    const vector<int>& getTasksIndex() const { return tasksIndex; }
    void setTable(int carNum, int edgeNum);
    float addPathInfo(int carIndex, const vector<int>& pathInfo, const Graph& G, int count);
    void addPath(const TimeWindow& tw, TimeWindowsByEdge::iterator insertIter);
    void clear();
    void clearFromIndex();

    void setTasksIndex(const vector<int>& ivec);

    const vector<TimeWindowsByCar>& getCarsTimeWindow() const { return _carAxis; }
    const TimeWindowsByCar& getCarTimeWindow(int carIndex) const { return _carAxis[carIndex]; }
    const TimeWindowsByEdge& getEdgeTimeWindow(int edgeIndex) const { return _edgeAxis[edgeIndex]; }
    TimeWindowsByEdge::iterator isCollision(int edgeIndex, const TimeWindow& tw);
    bool isPass(int edgeIndex, const TimeWindow& tw) {
        return isCollision(edgeIndex, tw) != _edgeAxis[edgeIndex].begin();
    }
private:
    vector<TimeWindowsByCar> _carAxis;
    vector<TimeWindowsByEdge> _edgeAxis;
    vector<int> tasksIndex;
    //int pointsIndex[MAX_CAR][MAX_TASK];
};

#endif // TIMEWINDOWTABLE_H
