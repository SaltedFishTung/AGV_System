#include "timewindow.h"
#include <math.h>

TimeWindow::TimeWindow(float enterTime, int len, int vel) {
    _enterTime = enterTime;
    _exitTime = _enterTime + (float)len/vel;
    _direction = true;
}

TimeWindow::TimeWindow(float enterTime, float exitTime, int carID, int edgeID) {
    _enterTime = enterTime;
    _exitTime = exitTime;
    _carID = carID;
    _edgeID = edgeID;
}

TimeWindow& TimeWindow::operator=(const TimeWindow& tw) {
    _enterTime = tw._enterTime;
    _exitTime = tw._exitTime;
    _direction = tw._direction;
    _carID = tw._carID;
    _edgeID = tw._edgeID;
}

void TimeWindow::setTime(float enterTime, float exitTime) {
    _enterTime = enterTime;
    _exitTime = exitTime;
}

void TimeWindow::setDirection(bool direction) {
    _direction = direction;
}

void TimeWindow::setCarID(int carID) {
    _carID = carID;
}

void TimeWindow::setEdgeID(int edgeID) {
    _edgeID = edgeID;
}

float TimeWindow::getEnterTime() const {
    return _enterTime;
}

float TimeWindow::getExitTime() const {
    return _exitTime;
}

bool TimeWindow::getDirection() const {
    return _direction;
}

int TimeWindow::getCarID() const {
    return _carID;
}

int TimeWindow::getEdgeID() const {
    return _edgeID;
}

void TimeWindow::changeTime(float time) {
    _exitTime += time - _enterTime;
    _enterTime = time;
}

ostream& operator<<(ostream& out, const TimeWindow& tw) {
    out << "[(" << tw.getCarID()+1 << ", " << tw.getEdgeID() << ", " << boolalpha << tw.getDirection() << "), "
        << "(" << tw.getEnterTime() << ", " << tw.getExitTime() << ")"
        << "]";
    return out;
}

bool operator==(const TimeWindow& arg1, const TimeWindow& arg2) {
    if(arg1._enterTime-arg2._enterTime > -1e-4 && arg1._enterTime-arg2._enterTime < 1e-4 &&
       arg1._exitTime-arg2._exitTime > -1e-4 && arg1._exitTime-arg2._exitTime < 1e-4 &&
       arg1._carID == arg2._carID && arg1._edgeID == arg2._edgeID)
        return true;
    return false;
}
