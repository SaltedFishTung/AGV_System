#ifndef AGV_GA_H
#define AGV_GA_H

#include <vector>
#include "graph.h"
using namespace std;

class AGV_GA
{
public:
    int taskNumber;
    int AGVNumber;
    double AGVSpeed;
    int populationGen;                     // 种群个数

    int crossoverProbability= 0.7;
    int mutateProbability = 0.2;

    AGV_GA();
    AGV_GA(Graph &G, vector<vector<int>> &task, vector<double> &timeAlreadyPassing,
           vector<vector<int>> &ongoingAGVPaths);
    void run();
private:
    Graph _graph;                           // 地图
    vector<vector<int>> _task;              // 任务集


    // 中间过程需要的变量
    vector<vector<double>> _AGVFitness;
    vector<vector<vector<int>>> _AGVPaths;
    vector<vector<int>> _taskSequence;
    vector<vector<double>> _AGVTimes;

    vector<vector<int>> _ongoingAGVPaths;   // 小车的行驶路径
    vector<double> _timeAlreadyPassing;     // 小车已运行时间
    vector<double> _timeForFinishingTasks;  // 存储小车完成任务还需要的时间

    // 任务分配的个体，任务次序
    vector<vector<int>> _taskDistribution;
    // 详细路径的个体，染色体
    vector<vector<vector<int>>> _priorityChromosomeSet;

    // 交叉概率矩阵以及变异概率矩阵
    vector<double> _crossverProbabilityArray;
    vector<double> _mutateProbabilityArray;

    double _currentMeanFitness;             // 当代适应度
    double _previousMeanFitness;            // 下一代适应度
    // 最优的任务分配
    vector<double> _taskDistributionElitist;
    // 最优的染色体
    vector<vector<int>> _priorityChromosomeSetElitist;



    void initialize();
    // 初始化交叉和概率矩阵
    void initializeCrossoverProbability();
    void initializeMutateProbability();

    // 初始化每个AGV计算还需要多长时间小车完成任务
    void initiateTimeLeftForFinishingTasks();

    // 对任务分配和染色体的交叉和变异操作
    void crossoverScheduling();
    void crossoverPrioritySet();
    void mutateScheduling();
    void mutatePrioritySet();

    // 确定任务序列
    void getTaskSequence(vector<vector<int>> &taskSequence);
    // 找到最早的空闲小车
    int getEarliestAGV(vector<double> &timeForFinishingTasks);
};

#endif // AGV_GA_H
