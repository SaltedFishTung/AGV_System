#ifndef TASKPROCESSOR_H
#define TASKPROCESSOR_H

#include <vector>
#include "task.h"
#include "car.h"
using namespace std;

class TaskProcessor {
public:
    TaskProcessor(const TaskSet& tSet, const CarSet& cSet) :
        _tSet(tSet), _cSet(cSet) {}
    vector<vector<int>> run() const;
private:
    TaskSet _tSet;
    CarSet _cSet;
};

#endif // TASKPROCESSOR_H
