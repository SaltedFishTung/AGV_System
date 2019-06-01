#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include "timewindowtable.h"
#include "taskprocessor.h"
#include "astar.h"
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

    void calculate(const Graph& G, const TaskSet& tSet, const CarSet& cSet);

    double getFitness() const;
    int getLongest() const;
    int getShortest() const;
    void setFitness(double fitness) { _fitness = fitness; }
    const TimeWindowTable& getTable() const { return _table; }

    void setCalculate(bool flag) { isCalculate = flag; }
    void setChange(bool flag) { isChange = flag; }

    void printGenes() const;
    void printTable();

    void clear() { _table.clear(); }

    const vector<int>& getCrossoverIndexArr() const { return crossoverIndexArr; }
    const vector<int>& getMutateIndexArr() const { return mutateIndexArr; }
    void setCrossoverIndexArr(const vector<int>& indexArr) { crossoverIndexArr = indexArr; }
    void setMutateIndexArr(const vector<int>& indexArr) { mutateIndexArr = indexArr; }

private:
    TimeWindowTable _table;

    // 基因组，代表的是每个车辆的任务执行顺序
    vector<vector<int>> genes;

    // 适应度相关
    double _fitness;
    int _longest;
    int _shortest;
    int _carNum;

    // 标记是否以及计算过，或者交叉(变异)过
    bool isCalculate;
    bool isChange;

    // 记录交叉、变异开始的起始坐标
    vector<int> crossoverIndexArr;
    vector<int> mutateIndexArr;

    // 分别用于初试计算和交叉(变异)后的计算
    void calculateFromHead(const Graph& G, const TaskSet& tSet, const CarSet& cSet);
    void calculateFromMiddle(const Graph& G, const TaskSet& tSet, const CarSet& cSet);

    void calculateReturnToFalse() { isCalculate = false; }
    void changeReturnToTrue() { isChange = true; }
};

vector<Chromosome> crossover(Chromosome arg1, Chromosome arg2);
Chromosome mutate(Chromosome arg);

#endif // CHROMOSOME_H
