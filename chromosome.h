#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include "taskprocessor.h"
#include "graph.h"
#include "task.h"
#include "car.h"
using namespace std;

class Chromosome {
public:
    friend vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2, int indexOf);
    friend Chromosome mutate(Chromosome arg);
    Chromosome() { _fitness = _longest = _shortest = _carNum = 0; }
    Chromosome(const Chromosome& Ch) {
        genes = Ch.genes;
        _fitness = Ch._fitness;
        _longest = Ch._longest;
        _shortest = Ch._shortest;
        _carNum = Ch._carNum;
    }
    Chromosome(const TaskProcessor& tPro) { genes = tPro.run();
                                            _fitness = _longest = _shortest = _carNum = 0; }
    Chromosome& operator =(const Chromosome& Ch) {
        genes = Ch.genes;
        _fitness = Ch._fitness;
        _longest = Ch._longest;
        _shortest = Ch._shortest;
        _carNum = Ch._carNum;
        return *this;
    }

    void calculate(const Graph& G, const TaskSet& tSet, const CarSet& cSet);
    int getFitness() const;
    int getLongest() const;
    int getShortest() const;
    void printGenes() const;
private:
    vector<vector<int>> genes;
    int _fitness;
    int _longest;
    int _shortest;
    int _carNum;
};

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2, int indexOf);
Chromosome mutate(Chromosome arg);

#endif // CHROMOSOME_H
