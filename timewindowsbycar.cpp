#include "timewindowsbycar.h"

TimeWindowsByCar::TimeWindowsByCar() {

}

void TimeWindowsByCar::adjustTime(int index) {
    list<TimeWindow>::iterator iter = this->begin();
}

ostream& operator<<(ostream& out, TimeWindowsByCar& twList) {
    cout << "car " << twList.front().getCarID() << ": ";
    auto iter = twList.begin();
    while (++iter != twList.end()) {
        cout << *iter << "-->";
    }
    return out;
}
