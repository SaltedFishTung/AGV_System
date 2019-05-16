#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "timewindowtable.h"
#include "chromosome.h"
using namespace std;

Chromosome::Chromosome() {
    _longest = _shortest = _carNum = 0;
    _fitness = 0.0;
}

Chromosome::Chromosome(const TaskProcessor &tPro, const Graph &G)
    : genes(tPro.run()) {
    //cout << "enter" << endl;
    _fitness = _longest = _shortest = 0;
    _carNum = genes.size();
    _table.setTable(_carNum, G.getEdgeNum());
    //cout << _carNum << "---" << G.getEdgeNum() << endl;
}

Chromosome::~Chromosome() {
    genes.clear();
}

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2, int indexOf) {
    for(int i = 0; i < arg1._carNum; i++) {
        int pos = indexOf;
        while(pos < arg1.genes[i].size() && arg1.genes[i].size() == arg2.genes[i].size()) {
            //cout << pos << "  " << arg1.genes[i].size() << " " <<
            //        arg2.genes[i].size() << endl;
            //cout << "-------------" << endl;
            int fir = -1, sec = -1;
            for(int j = 0; j < arg1.genes[i].size(); j++)
                if(arg1.genes[i][j] == arg2.genes[i][pos]) {
                    fir = j;
                    break;
                }
            for(int j = 0; j < arg2.genes[i].size(); j++)
                if(arg2.genes[i][j] == arg1.genes[i][pos]) {
                    sec = j;
                    break;
                }
            swap(arg1.genes[i][pos], arg2.genes[i][pos]);
            if(fir != -1 && sec != -1)
                swap(arg1.genes[i][fir], arg2.genes[i][sec]);
            else if(fir == -1 && sec != -1) {
                arg2.genes[i][sec] = arg1.genes[i][pos];
            } else if(fir != -1 && sec == -1)
                arg1.genes[i][fir] = arg2.genes[i][pos];
            pos++;
        }
    }
    return vector<Chromosome>{arg1, arg2};
}

Chromosome mutate(Chromosome arg) {
    int indexOf = arg.genes[arg.getLongest()].size()-1;
    if(indexOf < 0)
        return arg;
    arg.genes[arg.getShortest()].push_back(
                arg.genes[arg.getLongest()][indexOf]);
    arg.genes[arg.getLongest()].erase(arg.genes[arg.getLongest()].begin()+indexOf);
    return arg;
}

void Chromosome::calculate(const Graph& G, const TaskSet& tSet, const CarSet& cSet) {
    _carNum = 0;
    float minFit = numeric_limits<float>::max();
    float maxFit = numeric_limits<float>::min();
    float fitness[genes.size()];
    Graph graph(G);
    _table.clear();
    //_table.setTable(_carNum, G.getEdgeNum());
    for(int i = 0; i < genes.size(); i++)
        fitness[i] = 0.0;
//    for(auto gene : genes) {
//        for(auto item : gene)
//            cout << item << "--";
//        cout << endl;
//    }
    for(int carIndex = 0; carIndex < genes.size(); carIndex++) {
        int start = cSet[carIndex].startId;
        int end = tSet[genes[carIndex][0]].s;
        //cout << "out: " << start << "  " << end << endl;
        vector<int> pathInfo(G.getPathInfo(start, end));
        _table.addPathInfo(carIndex, pathInfo, graph, 1);
        //cout << fitness[carIndex] << "  ";
    }
    //cout << "finish tw init" << endl;
    //cout << _table;
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
    //cout << "  " << genes.size() << endl;
    for(int i = 0; i < genes.size(); i++) {
        //cout << fitness[i] << endl;
        if(maxFit < fitness[i]) {
            _longest = i;
            _fitness = fitness[i];
            maxFit = fitness[i];
        }
        if(minFit > fitness[i]) {
            _shortest = i;
            minFit = fitness[i];
        }
    }
}

float Chromosome::getFitness() const {
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
