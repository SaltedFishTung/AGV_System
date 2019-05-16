#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#define SMALLTOBIG 1
#define BIGTOSMALL -1

#include <iostream>
using namespace std;

class TimeWindow {
public:
    friend ostream& operator<<(ostream& out, const TimeWindow& tw);

    TimeWindow(float enterTime, float exitTime) : _enterTime(enterTime), _exitTime(exitTime) { }
    TimeWindow(float enterTime, float exitTime, int carID, int edgeID);
    TimeWindow(float enterTime, int len, int vel);
    void setTime(float enterTime, float exitTime);
    void setDirection(bool direction);
    void setCarID(int carID);
    void setEdgeID(int edgeID);
    float getEnterTime() const;
    float getExitTime() const;
    bool getDirection() const;
    int getCarID() const;
    int getEdgeID() const;
    void changeTime(float time);
private:
    float _enterTime;
    float _exitTime;
    bool _direction;             // 方向，规定由小节点到大节点为1，大节点到小节点为-1
    int _carID;
    int _edgeID;
};

#endif // TIMEWINDOW_H
