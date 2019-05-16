#include "task.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

TaskSet::TaskSet(const string& tasksFilePath) {
    ifstream inTasks(tasksFilePath);
    string line;
    this->push_back(Task(-1, -1, -1));
    while(getline(inTasks, line)) {
        istringstream iss(line);
        string temp;
        int arr[3];
        int i = 0;
        // 填充，无效数据
        while(getline(iss, temp, ' ')) {
            arr[i++] = stoi(temp);
        }
        this->push_back(Task(arr[0], arr[1]-1, arr[2]-1));
    }
    inTasks.close();
}

void TaskSet::printTasks() const {
    auto iter = this->begin();
    while(iter != this->end()) {
        cout << iter->id << "  " << iter->s << "  " << iter->e << endl;
        iter++;
    }
}
