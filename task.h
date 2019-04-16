#ifndef TASK_H
#define TASK_H

#include <vector>
#include <iostream>
using namespace std;

class Task
{
public:
    int id;
    int s;
    int e;
    int priority;
    Task(int id, int s, int e, int priority=0) :
        id(id), s(s), e(e), priority(priority) {}
};

class TaskSet : public vector<Task> {
public:
    TaskSet() {}
    TaskSet(const string& tasksFilePath);
    ~TaskSet() {}
    void printTasks() const;
};

#endif // TASK_H
