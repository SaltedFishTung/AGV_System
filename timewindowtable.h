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

    TimeWindowTable() { }
    TimeWindowTable(int carNum, int edgeNum);
    TimeWindowTable& operator=(const TimeWindowTable& table) {
        _carAxis = table._carAxis;
        _edgeAxis = table._edgeAxis;
        return *this;
    }
    const vector<int>& getTasksIndex() const { return tasksIndex; }
    void setTable(int carNum, int edgeNum);
    float addPathInfo(int carIndex, const vector<int>& pathInfo, Graph& G, int count);
    void clear();
    void clearFromIndex();

    void setTasksIndex(const vector<int>& ivec);
    void setPointIndex(int carIndex, int pointIndex) {

    }

    const vector<TimeWindowsByCar>& getCarsTimeWindow() const { return _carAxis; }
    const TimeWindowsByCar& getCarTimeWindow(int carIndex) const { return _carAxis[carIndex]; }
private:
    vector<TimeWindowsByCar> _carAxis;
    vector<TimeWindowsByEdge> _edgeAxis;


    TimeWindowsByEdge::iterator isCollision(int edgeIndex, const TimeWindow& tw);
    vector<int> tasksIndex;
    int pointsIndex[MAX_CAR][MAX_TASK];
};

#endif // TIMEWINDOWTABLE_H
