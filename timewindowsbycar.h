#ifndef TIMEWINDOWSBYCAR_H
#define TIMEWINDOWSBYCAR_H

#include <list>
#include <iostream>
#include "timewindow.h"
using namespace std;

class TimeWindowsByCar : public list<TimeWindow> {
public:
    friend ostream& operator<<(ostream& out, TimeWindowsByCar& twList);

    TimeWindowsByCar();
    TimeWindowsByCar(const TimeWindow& tw) { push_back(tw); }
    void adjustTime(int index);
};

#endif // TIMEWINDOWSBYCAR_H
