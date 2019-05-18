#ifndef TIMEWINDOWSBYCAR_H
#define TIMEWINDOWSBYCAR_H

#include <list>
#include <iostream>
#include "timewindow.h"
using namespace std;

class TimeWindowsByCar : public list<TimeWindow> {
public:
    friend ostream& operator<<(ostream& out, const TimeWindowsByCar& twList);

    TimeWindowsByCar();
    TimeWindowsByCar(const TimeWindow& tw) { push_back(tw); }
    void adjustTime(int index);
};

ostream& operator<<(ostream& out, const TimeWindowsByCar& twList);

#endif // TIMEWINDOWSBYCAR_H
