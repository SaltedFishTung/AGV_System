#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>
#include "timewindowtable.h"
#include "chromosome.h"
using namespace std;

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2) {
    vector<int> posArr;
    for(int i = 0; i < arg1._carNum; i++) {
        // 生成变异的区间[pos, size)
        int pos1 = rand()%arg1.genes[i].size();
        int pos2 = rand()%arg2.genes[i].size();
        int pos = min(pos1, pos2);
        int size = min(arg1.genes[i].size(), arg2.genes[i].size());
        posArr.push_back(pos);

        // fir, sec用来表示交换后是否出现任务重复
        // -1表示没有找到，即任务并不重复
        while (pos < size) {
            int fir = -1, sec = -1;
            for(int j = 0; j < arg1.genes[i].size(); j++) {
                if(arg1.genes[i][j] == arg2.genes[i][pos]) {
                    fir = j;
                    break;
                }
            }
            for(int j = 0; j < arg2.genes[i].size(); j++) {
                if(arg2.genes[i][j] == arg1.genes[i][pos]) {
                    sec = j;
                    break;
                }
            }
            swap(arg1.genes[i][pos], arg2.genes[i][pos]);
            if(fir != -1 && sec != -1)
                swap(arg1.genes[i][fir], arg2.genes[i][sec]);
            else if(fir == -1 && sec != -1)
                arg2.genes[i][sec] = arg1.genes[i][pos];
            else if(fir != -1 && sec == -1)
                arg1.genes[i][fir] = arg2.genes[i][pos];
            ++pos;
        }
    }
    arg1.isCalculate = arg2.isCalculate = false;
    arg1.isChange = arg2.isChange = true;

    arg1._table.setTasksIndex(posArr);
    arg2._table.setTasksIndex(posArr);

    return vector<Chromosome>{arg1, arg2};
}

Chromosome mutate(Chromosome arg) {
    int isMuate[4];
    // 产生变异的分支
    for(int i = 0; i < 4; i++)
        isMuate[i] = rand()%2;
    if(isMuate[0] + isMuate[1] + isMuate[2] + isMuate[3] == 0)
        isMuate[rand()%4] = 1;

    vector<int> posArr;
    for(int i = 0; i < 4; i++) {
        if(isMuate[i]) {
            // 生成变异区间[minPos, maxPos)
            int pos1 = rand()%arg.genes[i].size();
            int pos2 = rand()%arg.genes[i].size();
            int minPos = min(pos1, pos2);
            int maxPos = max(pos1, pos2) + 1;
            posArr.push_back(minPos);
            // 反转--变异
            reverse(arg.genes[i].begin()+minPos, arg.genes[i].begin()+maxPos);
        } else
            posArr.push_back(arg.genes[i].size());
    }

    arg._table.setTasksIndex(posArr);
    arg.isCalculate = false;
    arg.isChange = true;

    return arg;
}

Chromosome::Chromosome() {
    _longest = _shortest = _carNum = 0;
    _fitness = 0.0;
    isCalculate = false;
    isChange = false;
}

Chromosome::Chromosome(const TaskProcessor &tPro, const Graph &G)
    : genes(tPro.run()) {
    _fitness = _longest = _shortest = 0;
    _carNum = genes.size();
    _table.setTable(_carNum, G.getEdgeNum());
    isCalculate = false;
    isChange = false;
}

Chromosome::Chromosome(const Chromosome &Ch) {
    genes = Ch.genes;
    _fitness = Ch._fitness;
    _longest = Ch._longest;
    _shortest = Ch._shortest;
    _carNum = Ch._carNum;
    _table = Ch._table;

    isCalculate = Ch.isCalculate;
    isChange = false;
}

Chromosome::~Chromosome() {
}

Chromosome& Chromosome::operator =(const Chromosome& Ch) {
    genes = Ch.genes;
    _fitness = Ch._fitness;
    _longest = Ch._longest;
    _shortest = Ch._shortest;
    _carNum = Ch._carNum;
    _table = Ch._table;
    return *this;
}

void Chromosome::calculate(const Graph& G, const TaskSet& tSet, const CarSet& cSet) {
    if(isCalculate)
        return;
//    if(isChange) {
//        vector<int> tasksIndex = _table.getTasksIndex();
//        for(int carIndex = 0; carIndex < genes.size(); carIndex++) {
//            if()
//        }
//        _table.clearFromIndex();
//    }
    _carNum = 0;
    float minFit = numeric_limits<float>::max();
    float maxFit = numeric_limits<float>::min();
    float fitness[genes.size()];
    Graph graph(G);
    _table.clear();
    for(int i = 0; i < genes.size(); i++)
        fitness[i] = 0.0;
    for(int carIndex = 0; carIndex < genes.size(); carIndex++) {
        int start = cSet[carIndex].startId;
        int end = tSet[genes[carIndex][0]].s;
        vector<int> pathInfo(G.getPathInfo(start, end));
        _table.addPathInfo(carIndex, pathInfo, graph, 1);
    }
    int taskIndex = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for(int carIndex = 0; carIndex < genes.size(); carIndex++) {
            if(taskIndex < genes[carIndex].size()) {
                vector<int> pathInfo1(
                    G.getPathInfo(tSet[genes[carIndex][taskIndex]].s,
                    tSet[genes[carIndex][taskIndex]].e));
                fitness[carIndex] = _table.addPathInfo(carIndex, pathInfo1, graph, 1);
                _table.getCarTimeWindow(carIndex).size();
            }
            if(taskIndex < genes[carIndex].size()-1) {
                vector<int> pathInfo2(
                    G.getPathInfo(tSet[genes[carIndex][taskIndex]].e,
                    tSet[genes[carIndex][taskIndex+1]].s));
                _table.addPathInfo(carIndex, pathInfo2, graph, 1);
                flag = true;
            }
        }
        taskIndex++;
    }
    for(int i = 0; i < genes.size(); i++) {
        if(maxFit < fitness[i]) {
            _longest = i;
            _fitness = (double)1.0/fitness[i];
            maxFit = fitness[i];
        }
        if(minFit > fitness[i]) {
            _shortest = i;
            minFit = fitness[i];
        }
    }
    isCalculate = true;
}

double Chromosome::getFitness() const {
    return _fitness;
}

int Chromosome::getLongest() const {
    return _longest;
}

int Chromosome::getShortest() const {
    return _shortest;
}

void Chromosome::printGenes() const {
    for(auto gene : genes) {
        for(auto ver : gene)
            cout << ver << "  ";
        cout << endl;
    }
}

void Chromosome::printTable() {
    cout << _table << endl;
}

void Chromosome::calculateFromMiddle(const Graph& G, const TaskSet& tSet, const CarSet& cSet) {

}
