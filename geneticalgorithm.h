#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <iomanip>
#include <memory>
#include "car.h"
#include "task.h"
#include "graph.h"
#include "chromosome.h"
using namespace std;
#define MAX_GENERATION 256;
#define MIN_GENERATION 64;
#define MIN_ERROR 0.000005

class GeneticAlgorithm {
public:
    int population;
    int taskNum;
    int carNum;
    double crossoverProbability;
    double mutateProbability;

    GeneticAlgorithm(CarSet& cSet, TaskSet& tSet, Graph& graph) :
        _cSet(cSet), _tSet(tSet), _graph(graph) { }

    void run();
    const vector<TimeWindowsByCar>& getResultPath() const {
        return _bestChromosome.getTable().getCarsTimeWindow();
    }
private:
    // 输入，车辆集、任务集、地图
    CarSet _cSet;
    TaskSet _tSet;
    Graph _graph;

    // 最优染色体以及每一代的所有染色体
    Chromosome _bestChromosome;
    vector<Chromosome> _chromosomeSet;

    // 交叉概率组、变异概率组
    vector<double> _crossoverProbabilityArray;
    vector<double> _mutateProbabilityArray;

    // 总适应度
    double _totalFitness;

    // 初始化函数
    void initGA();
    void initializeCrossoverProbability();
    void initializeMutateProbability();

    // 轮盘赌，计算适应度、总积适应度
    void calculateFitness();
    void calculateTotalFitness();

    // 选择、交叉、变异
    void selectChromosome();         // 轮盘制选择染色体
    void crossoverChromosome();
    void mutateChromosome();
};

#endif // GENETICALGORITHM_H
