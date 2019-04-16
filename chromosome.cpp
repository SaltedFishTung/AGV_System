#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <algorithm>
#include "chromosome.h"
#include "taskprocessor.h"
#include "graph.h"
#include "task.h"
#include "car.h"
using namespace std;

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2, int indexOf) {
    //arg1.printGenes();
    //cout << "------------------------" << endl;
    //arg2.printGenes();
    //cout << "++++++++++++++++++++++++" << indexOf << endl;
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
    //cout << "enter" << endl;
    //cout << genes.size() << endl;
    _carNum = 0;
    int maxFit = INT_MIN, minFit = INT_MAX;
    int fitness[genes.size()];
    for(int i = 0; i < genes.size(); i++)
        fitness[i] = 0;
    //printGenes();
    //G.printDist();
    //tSet.printTasks();
    for(vector<int> gene : genes) {
        //cout << "calculate fitness" << endl;
        // 小车起始位置到第一个任务的起点
        fitness[_carNum] += G.getShortestDist(cSet[_carNum].verId, tSet[gene[0]].s);
        //cout << cSet[_carNum].verId << "  " << gene[0] << "  " << tSet[gene[0]].s << endl;
        //cout << _carNum << "  " << fitness[_carNum] << endl;
        for(int i = 0; i < gene.size()-1; i++) {
            //cout << "enter" << endl;
            //cout << G.getShortestDist(tSet[gene[i]].s, tSet[gene[i]].e) << endl;
            fitness[_carNum] += G.getShortestDist(tSet[gene[i]].s, tSet[gene[i]].e);
        }
        _carNum++;
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
    //cout << _fitness << endl;
    //cout << endl;
}

int Chromosome::getFitness() const {
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
