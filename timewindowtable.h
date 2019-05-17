#ifndef TIMEWINDOWTABLE_H
#define TIMEWINDOWTABLE_H

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

    void setTable(int carNum, int edgeNum);
    int addTimeWindow(int carIndex, int edgeIndex);
    float addPathInfo(int carIndex, const vector<int>& pathInfo, Graph& G, int count);
    TimeWindowsByEdge::iterator isCollision(int edgeIndex, const TimeWindow& tw);
    void clear();
private:
    vector<TimeWindowsByCar> _carAxis;
    vector<TimeWindowsByEdge> _edgeAxis;
};

#endif // TIMEWINDOWTABLE_H
