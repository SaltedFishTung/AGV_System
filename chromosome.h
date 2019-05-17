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
    friend vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2);
    friend Chromosome mutate(Chromosome arg);
    Chromosome();
    Chromosome(const TaskProcessor& tPro, const Graph& G);
    Chromosome(const Chromosome& Ch);
    Chromosome& operator=(const Chromosome& Ch);
    ~Chromosome();

    void calculate(const Graph& G, const TaskSet& tSet, const CarSet& cSet);
    double getFitness() const;
    int getLongest() const;
    int getShortest() const;
    void returnToFalse() { isCalculate = false; }
    void printGenes() const;
    void printTable();
    void clear() { _table.clear(); }

    int getCrossoverIndex() const { return crossoverIndex; }
    int getMutateIndex() const { return mutateIndex; }
    void setCrossoverIndex(int index) { crossoverIndex = index; }
    void setMutateIndex(int index) { mutateIndex = index; }

private:
    TimeWindowTable _table;
    vector<vector<int>> genes;
    double _fitness;
    int _longest;
    int _shortest;
    int _carNum;
    bool isCalculate;
    int crossoverIndex;
    int mutateIndex;
};

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2);
Chromosome mutate(Chromosome arg);

#endif // CHROMOSOME_H
