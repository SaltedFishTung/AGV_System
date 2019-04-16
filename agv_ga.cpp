#include "agv_ga.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

AGV_GA::AGV_GA(){

}

AGV_GA::AGV_GA(Graph &G, vector<vector<int> > &task, vector<double> &timeAlreadyPassing,
               vector<vector<int> > &ongoingAGVPaths) {
    _graph = G;
    _task = task;
    _timeAlreadyPassing = timeAlreadyPassing;
    _ongoingAGVPaths = ongoingAGVPaths;

    taskNumber = task.size();
    AGVNumber = ongoingAGVPaths.size();
}

void AGV_GA::run() {
    int stateTimes = 0;
    int evolveTimes = 0;
    // 每个子代每辆小车的路径

    while((stateTimes > 10 && evolveTimes > 50) || evolveTimes > 200) {
        // 交叉操作
        initializeCrossoverProbability();
        crossoverScheduling();
        crossoverPrioritySet();

        // 变异操作
        initializeMutateProbability();
        mutateScheduling();
        mutatePrioritySet();
        int count;  // 第count个任务
        int i = 0;  // 第i代

        for(vector<vector<int>> generationForAGVPaths : _AGVPaths) {
            count = 0;
            while (count < taskNumber) {
                // count记录任务数
                // 获取剩余时间最少的AGV空闲小车
                int AGVIndex = getEarliestAGV(AGVTimes.get(i));
                if(_timeAlreadyPassing[AGVIndex] == -1) {
                    // 未分配
                }
                // path1:从上一次任务终点到这一次任务起点
                // path2:从这一次任务起点到这一次任务终点
                vector<int> path1;
                vector<int> path2;
            }
        }
    }
}

void AGV_GA::initialize() {
    for(int i = 0; i < populationGen; i++) {
        vector<int> task;
        vector<vector> priChromosome;
        // encode，随机将任务分配给车，索引代表任务编号，值代表小车编号
        srand(time(0));
        for(int j = 0; j < taskNumber; j++)
            task[j] = rand()%taskNumber + 1;
        // encode，染色体分配
        for(int j = 0; j < taskNumber*2; j++) {
            for(int k = 0; k < _graph.getVerNum(); k++)
                priChromosome[j][k] = rand()%_graph.getVerNum();
        }
        _taskDistribution.push_back(task);
        _priorityChromosomeSet.push_back(priChromosome);
    }

    // 初始化小车适应度
    for (int i = 0; i < populationGen; i++) {
        vector<double> AGVFitnessGeneration;
        for (int j = 0; j < AGVNumber; j++) {
            AGVFitnessGeneration[j] = 0;
        }
        _AGVFitness.push_back(AGVFitnessGeneration);
    }

    // 初始化各子代每辆小车路径
    for (int i = 0; i < populationGen; i++) {
        vector<vector<int>> generationForAGVPaths;
        for (vector<int> path : ongoingAGVPaths) {
            generationForAGVPaths.push_back(path);
        }
        _AGVPaths.push_back(generationForAGVPaths);
    }

    // 初始化各子代每辆小车已用时间
    for (int i = 0; i < populationGen; i++) {
        vector<double> time;
        for (int j = 0; j < _timeForFinishingTasks.length; j++) {
            time[j] = timeForFinishingTasks[j];
        }
        _AGVTimes.push_back(time);
    }

    // 任务分配，任务次序代表执行顺序，元素值代表执行的任务编号
    // 例如任务序列3、1、4、2代表任务执行顺序为3->1->4->2
    getTaskSequence(_taskSequence);
}

void AGV_GA::initializeCrossoverProbability() {
    srand(time(0));
    for(int i = 0; i < populationGen; i++)
        _crossverProbabilityArray[i] = rand()%100/(double)101;
}

void AGV_GA::initializeMutateProbability() {
    srand(time(0));
    for(int i = 0; i < populationGen; i++)
        _mutateProbabilityArray[i] = rand()%100/(double)101;
}

void AGV_GA::initiateTimeLeftForFinishingTasks() {
    //初始化剩余时间数组
    for (int i = 0; i < timeForFinishingTasks.length; i++)
        _timeForFinishingTasks[i] = (double)-1;
    //如果小车闲置(为-1)，给数组赋值0
    for (int i = 0; i < _timeAlreadyPassing.length; i++) {
        if (_timeAlreadyPassing[i]==-1) {
            _timeForFinishingTasks[i] = (double)0;
        }
    }

    for (int i = 0; i < AGVNumber; i++) {
        //对于没有闲置的车,计算他们还要多长时间完成任务，整个路程的时间减去已经开了多久
        double distance = 0;
        if (_timeForFinishingTasks[i]!=0)  {
            for (int j = 0; j+1 < _ongoingAGVPaths.get(i).size(); j++) {
                distance += _graph.Dijstra(_ongoingAGVPaths.get(i).get(j), _ongoingAGVPaths.get(i).get(j+1));
            }
            _timeForFinishingTasks[i] = distance/AGVSpeed - _timeAlreadyPassing[i];
        }
    }
}

void AGV_GA::crossoverScheduling() {
    srand(time(0));
    for(int i = 0; i+1 < populationGen; i+=2) {
        // 概率值达到要求的话，进行交叉
        if(_crossverProbabilityArray[i] <= crossoverProbability) {
            // 子代1、2从父代1、2交叉获取子代
            int p1 = rand()%(taskNumber-1);
            int p2 = rand()%(taskNumber-p1)+p1;
            vector<int> newGen1;
            vector<int> newGen2;
            vector<int> parent1;
            vector<int> parent2;
            for(int j = 0; j < p1; j++) {
                newGen1[j] = parent1[j];
                newGen2[j] = parent2[j];
            }
            for (int j = p2 + 1; j < taskNumber; j++) {
                newGen1[j] = parent1[j];
                newGen2[j] = parent2[j];
            }
            for (int j = point1; j <= point2; j++) {
                newGen1[j] = parent2[j];
                newGen2[j] = parent1[j];
            }
        }
        _taskDistribution.push_back(newGen1);
        _taskDistribution.push_back(newGen2);
    }
}

void AGV_GA::crossoverPrioritySet() {
    int priChromosomeLen = _priorityChromosomeSet[0].size();
    srand(time(0));
    for(int i = 0; i+1 < populationGen; i+=2) {
        // 概率值达到要求的话，进行交叉
        if(_crossverProbabilityArray[i] <= crossoverProbability) {
            int point = rand()%(_graph.getVerNum()-1);
            vector<vector<int>> newGen1;
            vector<vector<int>> newGen2;
            vector<vector<int>> parent1;
            vector<vector<int>> parent2;
            vector<vector<int>> sortArr1;
            vector<vector<int>> sortArr2;
            for(int j = 0; j < priChromosomeLen; j++) {
                for(int k = 0; k <= point; k++) {
                    newGen1[j][k] = parent1[j][k];
                    newGen2[j][k] = parent2[j][k];
                }
            }
            for (int j = 0; j < priChromosomeLen; j++) {
                int count = 0;
                for(int k = point+1; k < _graph.getVerNum(); k++) {
                    sortArr1[j][count] = parent1[j][k];
                    sortArr2[j][count] = parent2[j][k];
                    newGen1[j][k] = parent2[j][k];
                    newGen2[j][k] = parent1[j][k];
                    count++;
                }
            }
            for (int j = 0; j < priChromosomeLength; j++) {
                sort(sortArr1[j].begin(), sortArr1[j].end());
                sort(sortArr2[j].begin(), sortArr2[j].end());
            }
            for (int p = 0; p < priChromosomeLength; p++) {
                for (int l = 1; l < nodeSize-point; l++) {
                    for (int j = 0; j < nodeSize-point-1; j++) {
                        if (newGen1[p][point + l] == sortArr2[p][j]) {
                            newGen1[p][point + l] = sortArr1[p][j];
                        }
                        if (newGen2[p][point + l] == sortArr1[p][j]) {
                            newGen2[p][point + l] = sortArr2[p][j];
                        }
                    }
                }
            }
        }
        _priorityChromosomeSet.push_back(newGen1);
        _priorityChromosomeSet.push_back(newGen2);
    }
}

void AGV_GA::mutateScheduling() {
    int currentPopulationSize = _taskDistribution.size();
    srand(time(0));
    for (int i = 0; i < currentPopulationSize; i++) {
        if (mutateProbabilityArray[i] <= mutationProbability) {
            vector<int> newGeneration;
            for (int j = 0; j < taskNumber; j++) {
                //j代表第几个任务，值对应哪一个车
                newGeneration[j] = rand()%AGVNumber+1;
            }
            taskDistribution.add(newGeneration);
        }
    }
}

void AGV_GA::mutatePrioritySet() {
    vector<vector<int>> newGenrationList;
    int count = 0;
    for(auto parent : _priorityChromosomeSet) {
        if(_mutateProbabilityArray[count] <= mutateProbability) {
            vector<vector<int>> newGeneration;
            for(int k = 0; k < parent.size(); k++) {
                int p1 = rand()%(_graph.getVerNum());
                int p2 = rand()%(_graph.getVerNum());
                int mutatePoint = parent[k][p1];
                for(int i = 0; i < _graph.getVerNum(); i++)
                    newGeneration[k][i] = parent[k][i];
                for (int i = point1; i + 1 < nodeSize; i++)
                    newGeneration[k][i] = newGeneration[k][i + 1];
                for (int i = nodeSize - 1; i - 1 >= point2; i--)
                    newGeneration[k][i] = newGeneration[k][i - 1];
                newGeneration[k][point2] = mutatedPoint;
            }
            newGenerationList.add(newGeneration);
        }
        count++;
    }
    for(auto newGenration : newGenrationList)
        _priorityChromosomeSet.push_back(newGenration);
}

void AGV_GA::getTaskSequence(vector<vector<int>> &taskSequence) {
    for (vector<int> tasksCode : _taskDistribution) {
        vector<int> sortArray;
        for (int i = 0; i < taskNumber; i++) {
            sortArray[i] = tasksCode[i];
        }
        sort(sortArray.begin(), sortArray.end());
        vector<int> sequence;
        //最小的最早开始做，任务序号存在sequence中
        for (int i = 0; i < taskNumber; i++) {
            for (int j = 0; j < taskNumber; j++) {
                if (tasksCode[j] == sortArray[i]) {
                    sequence[i] = j;
                    break;
                }
            }
        }
        taskSequence.add(sequence);
    }
}

int AGV_GA::getEarliestAGV(vector<double> &timeForFinishingTasks) {
    vector<double> sortTimeArray;
    for (int i = 0; i < timeForFinishingTasks.length; i++) {
        sortTimeArray[i] = timeForFinishingTasks[i];
    }
    sort(sortTimeArray.begin(), sortTimeArray.end());
    //找到剩余完成任务时间最少的小车
    for (int i = 0; i < timeForFinishingTasks.length; i++) {
        if (timeForFinishingTasks[i] == sortTimeArray[0]) {
            return i;
        }
    }
    //出问题
    return -1;
}
