#ifndef TIMEWINDOWSBYEDGE_H
#define TIMEWINDOWSBYEDGE_H

#include <list>
#include <iostream>
#include "timewindow.h"
using namespace std;

class TimeWindowsByEdge : public list<TimeWindow> {
public:
    friend ostream& operator<<(ostream& out, TimeWindowsByEdge& twList);

    TimeWindowsByEdge();
    TimeWindowsByEdge(const TimeWindow& tw) { push_back(tw); }
    TimeWindowsByEdge::iterator canEnter(const TimeWindow& currentTimeWindow);
private:
    TimeWindowsByEdge::iterator onlyOneCanEnter(const TimeWindow& currentTimeWindow);
};

#endif // TIMEWINDOWSBYEDGE_H
