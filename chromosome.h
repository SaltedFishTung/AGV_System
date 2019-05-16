#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include "timewindowtable.h"
#include "taskprocessor.h"
#include "graph.h"
#include "task.h"
#include "car.h"
using namespace std;

class Chromosome {
public:
    friend vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2, int indexOf);
    friend Chromosome mutate(Chromosome arg);
    Chromosome();
    Chromosome(const TaskProcessor& tPro, const Graph& G);
    Chromosome& operator =(const Chromosome& Ch) {
        genes = Ch.genes;
        _fitness = Ch._fitness;
        _longest = Ch._longest;
        _shortest = Ch._shortest;
        _carNum = Ch._carNum;
        _table = Ch._table;
        return *this;
    }
    ~Chromosome();

    void calculate(const Graph& G, const TaskSet& tSet, const CarSet& cSet);
    float getFitness() const;
    int getLongest() const;
    int getShortest() const;
    void printGenes() const;
    void printTable();
    void clear() { _table.clear(); }
private:
    TimeWindowTable _table;
    vector<vector<int>> genes;
    float _fitness;
    int _longest;
    int _shortest;
    int _carNum;
};

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2, int indexOf);
Chromosome mutate(Chromosome arg);

#endif // CHROMOSOME_H
