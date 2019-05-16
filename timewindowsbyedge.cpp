#include "timewindowsbyedge.h"
#include "timewindow.h"

TimeWindowsByEdge::TimeWindowsByEdge() {

}

TimeWindowsByEdge::iterator TimeWindowsByEdge::canEnter(const TimeWindow &currentTimeWindow) {
    // 该路段尚未有时间窗
    if(this->size() == 1)
        return this->end();
    // 该路段只有一个时间窗
    if(this->size() == 2)
        return onlyOneCanEnter(currentTimeWindow);
    TimeWindowsByEdge::iterator currIter = this->begin();
    ++currIter;
    TimeWindowsByEdge::iterator nextIter = currIter;
    ++nextIter;
    TimeWindowsByEdge::iterator backIter = this->end();
    --backIter;
    while(nextIter != this->end()) {
        bool flag_curr = (currIter->getDirection() == currentTimeWindow.getDirection());
        bool flag_next = (nextIter->getDirection() == currentTimeWindow.getDirection());
        // 该段相邻的两个时间窗方向与当前车方向都相同时
        if(flag_curr && flag_next){
            // 车在两个占用时间窗之前进入路段
            if(currIter->getEnterTime() > currentTimeWindow.getEnterTime())
                return currIter;
            // 车在两个时间窗之间进入路段
            else if(nextIter->getEnterTime() > currentTimeWindow.getEnterTime())
                return nextIter;
            // 车在两个时间窗之后进入
            else if(nextIter->getEnterTime() < currentTimeWindow.getEnterTime() &&
                    nextIter == backIter)
                return this->end();
        }
        // 该段相邻的两个时间窗方向前一个与当前车方向相同，后一个相向
        else if(flag_curr && !flag_next){
            // 在两者之前
            if(currIter->getEnterTime() > currentTimeWindow.getEnterTime())
                return currIter;
            // 在两者中间
            else if(nextIter->getEnterTime() > currentTimeWindow.getExitTime())
                return nextIter;
            // 在两者之后
            else if(nextIter->getExitTime() < currentTimeWindow.getEnterTime() &&
                    nextIter == backIter)
                return this->end();
            // 同一辆车来回时
            if(nextIter->getCarID() == currentTimeWindow.getCarID() &&
               nextIter->getExitTime() == currentTimeWindow.getEnterTime())
                return ++nextIter;
        }
        // 该段相邻的两个时间窗方向前一个与当前车方向相向，后一个相同
        else if(!flag_curr && flag_next) {
            // 同一辆车来回时
            if(currIter->getCarID() == currentTimeWindow.getCarID() &&
               currIter->getExitTime() == currentTimeWindow.getEnterTime() &&
               nextIter->getEnterTime() > currentTimeWindow.getEnterTime())
                return nextIter;

            // 不是同一辆车时
            // 在两者之前
            if(currIter->getEnterTime() > currentTimeWindow.getExitTime())
                return currIter;
            // 在两者之间
            else if(nextIter->getEnterTime() > currentTimeWindow.getEnterTime())
                return nextIter;
            // 在两者之后
            else if(nextIter->getEnterTime() < currentTimeWindow.getEnterTime() &&
                    nextIter == backIter)
                return this->end();
        }
        // 该段相邻的两个时间窗方向与当前车方向都相向时
        else if(!flag_curr && !flag_next) {
            // 同一辆车来回时
            if(currIter->getCarID() == currentTimeWindow.getCarID() &&
               currIter->getExitTime() == currentTimeWindow.getEnterTime() &&
               nextIter->getEnterTime() > currentTimeWindow.getExitTime())
                return nextIter;

            // 不是同一辆车时
            // 在两者之前
            if(currIter->getEnterTime() > currentTimeWindow.getExitTime())
                return currIter;
            // 在两者之间
            else if(currIter->getExitTime() < currentTimeWindow.getEnterTime() &&
                    nextIter->getEnterTime() > currentTimeWindow.getExitTime())
                return nextIter;
            // 在两者之后
            else if(nextIter->getExitTime() < currentTimeWindow.getEnterTime() &&
                    nextIter == backIter)
                return this->end();
            // 同一辆车来回时
            if(nextIter->getCarID() == currentTimeWindow.getCarID() &&
               nextIter->getExitTime() == currentTimeWindow.getEnterTime())
                return ++nextIter;
        }
        ++currIter;
        ++nextIter;
    }
    return this->begin();
}

TimeWindowsByEdge::iterator TimeWindowsByEdge::onlyOneCanEnter(const TimeWindow &currentTimeWindow) {
    auto backIter = this->end();
    --backIter;
    // 同一辆车
    if(this->back().getCarID() == currentTimeWindow.getCarID()) {
        // 车进入较晚
        if(this->back().getEnterTime() < currentTimeWindow.getEnterTime())
            return this->end();
        else
            return backIter;
    }
    // 车的方向与时间窗一致
    else if(this->back().getDirection() == currentTimeWindow.getDirection()) {
        // 车进入的时间较晚
        if(this->back().getEnterTime() < currentTimeWindow.getEnterTime())
            return this->end();
        // 车进入的时间较早
        else if(this->back().getEnterTime() > currentTimeWindow.getEnterTime()) {
            return backIter;
        } else  // 碰撞
            return this->begin();
    } else {    // 车的方向与时间窗相向
        // 车在进入前，该路段已经空出来
        if(this->back().getExitTime() < currentTimeWindow.getEnterTime())
            return this->end();
        // 车在离开后，该路段还未被占用
        else if(this->back().getEnterTime() > currentTimeWindow.getExitTime())
            return backIter;
        else
            return this->begin();
    }
    return this->begin();
}

ostream& operator<<(ostream& out, TimeWindowsByEdge& twList) {
    cout << "edge " << twList.front().getEdgeID() << ": ";
    auto iter = twList.begin();
    while (++iter != twList.end()) {
        cout << *iter << "-->";
    }
    return out;
}
