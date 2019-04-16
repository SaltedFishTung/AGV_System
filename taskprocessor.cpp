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
    //cout << time(0) << endl;
    //srand(time(0));
    // 生成随机序列
    int random[_tSet.size()];
    for(int i = 0; i < _tSet.size(); i++)
        random[i] = i;
    for(int i = _tSet.size()-1; i > 0; i--)
        swap(random[i], random[rand()%i]);

    for(int i = 0; i < _cSet.size(); i++) { // 第i辆车
        vector<int> taskSeq;
        for(int j = 0; j < _tSet.size(); j++) {
            // 给每辆车分配任务
            if(_tSet[random[j]].id % _cSet.size() == i)
                taskSeq.push_back(_tSet[random[j]].id);
        }
        result.push_back(taskSeq);
    }
    return result;
}
