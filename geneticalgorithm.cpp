#include "geneticalgorithm.h"
#include "car.h"
#include "task.h"
#include "graph.h"
#include "taskprocessor.h"
#include "chromosome.h"
#include <iostream>
#include <vector>
#include <limits.h>
#include <random>
#include <time.h>
using namespace std;

void GeneticAlgorithm::run() {
    clock_t startTime, endTime;
    startTime = clock();
    initGA();
    cout << "finish init" << endl;
    int stableTimes = 0;
    float lastFitness = 0.0;
    for(int count = 0; count < 200; count++) {
        //cout << "-----" << count << "-----" << endl;
        srand(time(0));
        // 选择 交叉 变异 一条龙服务
        //cout << "1---" << count << endl;
        selectChromosome();
        //cout << "2---" << count << endl;
        initializeCrossoverProbability();
        crossoverChromosome();
        //cout << "3---" << count << endl;
        initializeMutateProbability();
        mutateChromosome();
        //cout << "4---" << count << endl << endl;
        //_bestChromosome.printTable();
        //cout << setprecision(20) << _bestChromosome.getFitness() << endl;
        //cout << "-----------------------------" << endl;
        if(_bestChromosome.getFitness() - lastFitness <= MIN_ERROR)
            ++stableTimes;
        else
            stableTimes = 0;
        lastFitness = _bestChromosome.getFitness();
        if(stableTimes > 15)
            break;
    }
    endTime = clock();
    cout << endTime-startTime << " times" << endl;
//    for(const TimeWindowsByCar& twByCar : _bestChromosome.getTable().getCarsTimeWindow())
//        cout << twByCar << endl;
}

void GeneticAlgorithm::initGA() {
    // 随机生成种群
    population = 100;
    srand(time(0));
    _graph.run();
    for(int i = 0; i < population; i++) {
        TaskProcessor tPro(_tSet, _cSet);
        Chromosome ch(tPro, _graph);
        _chromosomeSet.push_back(ch);
    }
    crossoverProbability = 0.7;
    mutateProbability = 0.2;
    taskNum = _tSet.size();
    carNum = _cSet.size();
    _bestChromosome.setFitness(numeric_limits<double>::min());
}

void GeneticAlgorithm::initializeCrossoverProbability() {
    for(unsigned i = 0; i < _chromosomeSet.size(); i++)
        _crossoverProbabilityArray.push_back(((double)rand())/RAND_MAX);
}

void GeneticAlgorithm::initializeMutateProbability() {
    for(unsigned i = 0; i < _chromosomeSet.size(); i++)
        _mutateProbabilityArray.push_back(((double)rand())/RAND_MAX);
}

void GeneticAlgorithm::calculateFitness() {
    float maxFit = _bestChromosome.getFitness();
    int index = -1;
    for(unsigned i = 0; i < _chromosomeSet.size(); i++) {
        _chromosomeSet[i].calculate(_graph, _tSet, _cSet);
        if(maxFit < _chromosomeSet[i].getFitness())
            index = i;
    }
    if(index != -1)
        _bestChromosome = _chromosomeSet[index];
}

void GeneticAlgorithm::calculateTotalFitness() {
    _totalFitness = 0.0;
    for(const Chromosome& ch : _chromosomeSet)
        _totalFitness += ch.getFitness();
    //cout << "total: " << _totalFitness << endl;
}

void GeneticAlgorithm::selectChromosome() {
    clock_t startTime, endTime;
    vector<Chromosome> newChromosomeSet;
    int selectBestNum = population/4;
    startTime = clock();
    calculateFitness();
    calculateTotalFitness();
    endTime = clock();
    cout << "calculate cost " << endTime-startTime << " times" << endl;

    // 新种群的四分之一是最优染色体
    for(int i = 0; i < selectBestNum; i++)
        newChromosomeSet.push_back(_bestChromosome);
    // 剩下四分之三采取轮盘
    for(int i = 0; i < population-selectBestNum; i++) {
        double random = ((double)rand())/RAND_MAX;
        for(unsigned j = 0; j < _chromosomeSet.size(); j++) {
            if(random <= _chromosomeSet[i].getFitness()/_totalFitness) {
                newChromosomeSet.push_back(_chromosomeSet[j]);
                break;
            }
            else
                random -= _chromosomeSet[i].getFitness()/_totalFitness;
        }
    }
    _chromosomeSet = newChromosomeSet;
}

void GeneticAlgorithm::crossoverChromosome() {
    int ChromosomePopulation = _chromosomeSet.size();
    for(int i = 0; i+1 < ChromosomePopulation; i+=2) {
        if(_crossoverProbabilityArray[i] < crossoverProbability) {
            vector<Chromosome> chromosomeArr(
                        crossover(_chromosomeSet[i], _chromosomeSet[i+1]));
            _chromosomeSet.push_back(chromosomeArr[0]);
            _chromosomeSet.push_back(chromosomeArr[1]);
        }
    }
}

void GeneticAlgorithm::mutateChromosome() {
    int ChromosomePopulation = _chromosomeSet.size();
    for(int i = 0; i < ChromosomePopulation; i++) {
        if(_mutateProbabilityArray[i] < mutateProbability) {
            _chromosomeSet.push_back(mutate(_chromosomeSet[i]));
        }
    }
}
