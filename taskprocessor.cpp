#include "taskprocessor.h"
#include <vector>
#include <random>
#include <iostream>
#include <time.h>
#include "task.h"
#include "car.h"
using namespace std;

vector<vector<int>> TaskProcessor::run() const {
    vector<vector<int>> result;
    int random[_tSet.size()];
    for(int i = 1; i < _tSet.size(); i++)
        random[i] = i;
    for(int i = _tSet.size()-1; i > 1; i--)
        swap(random[i], random[rand()%i+1]);

    for(int i = 0; i < _cSet.size(); i++) { // 第i辆车
        //cout << i << "  ";
        vector<int> taskSeq;
        for(int j = 1; j < _tSet.size(); j++) {
            // 给每辆车分配任务
            if(_tSet[random[j]].id % _cSet.size() == i)
                taskSeq.push_back(_tSet[random[j]].id);
        }
        result.push_back(taskSeq);
    }
    //cout << "seq" << endl;
    return result;
}
