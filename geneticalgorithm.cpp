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
    initGA();
    cout << "finish init" << endl;
    for(int count = 0; count < 200; count++) {
        // 选择 交叉 变异 一条龙服务
        //cout << "1---" << count << endl;
        selectChromosome();
        //cout << "2---" << count << endl;
        crossoverChromosome();
        //cout << "3---" << count << endl;
        mutateChromosome();
        //cout << "4---" << count << endl << endl;
        _bestChromosome.printGenes();
        cout << _bestChromosome.getFitness() << endl << endl;
        cout << "-----------------------------" << endl;
    }
}

void GeneticAlgorithm::initGA() {
    // 随机生成种群
    population = 100;
    srand(time(0));
    for(int i = 0; i < population; i++) {
        TaskProcessor tPro(_tSet, _cSet);
        Chromosome ch(tPro);
        _chromosomeSet.push_back(ch);
        //ch.printGenes();
    }
    initializeCrossoverProbability();
    initializeMutateProbability();
    crossoverProbability = 0.7;
    mutateProbability = 0.2;
    taskNum = _tSet.size();
    carNum = _cSet.size();
    //cout << "finish init";
}

void GeneticAlgorithm::initializeCrossoverProbability() {
    srand(time(0));
    for(int i = 0; i < population; i++)
        _crossoverProbabilityArray.push_back(rand()%100/(double)101);
}

void GeneticAlgorithm::initializeMutateProbability() {
    srand(time(0));
    for(int i = 0; i < population; i++)
        _mutateProbabilityArray.push_back(rand()%100/(double)101);
}

void GeneticAlgorithm::selectChromosome() {
    //cout << "select" << endl;
    int indexOf = -1;
    int minFit = INT_MAX;
    //cout << "----" << _chromosomeSet.size() << "------" << endl;
    for(int i = 0; i < _chromosomeSet.size(); i++) {
        //cout << "enter  " << i << endl;
        //_chromosomeSet[i].printGenes();
        _chromosomeSet[i].calculate(_graph, _tSet, _cSet);
        //cout << _chromosomeSet[i].getFitness() << endl;
        //cout << "finish calculate" << endl;
        if(minFit > _chromosomeSet[i].getFitness()) {
            minFit = _chromosomeSet[i].getFitness();
            indexOf = i;
        }
    }
    _bestChromosome = _chromosomeSet[indexOf];
    vector<Chromosome> newChromosomeSet;
    for(int i = 0; i < population-(population/4); i++) {
        int pos = rand()%(_chromosomeSet.size());
        //cout << pos << endl;
        newChromosomeSet.push_back(_chromosomeSet[pos]);
    }
    for(int i = 0; i < population/4; i++)
        newChromosomeSet.push_back(_bestChromosome);
    _chromosomeSet = newChromosomeSet;
}

void GeneticAlgorithm::crossoverChromosome() {
    int ChromosomePopulation = _chromosomeSet.size();
    for(int i = 0; i+1 < ChromosomePopulation; i+=2) {
        //cout << "enter crossover  " << i << endl;
        //cout << _crossoverProbabilityArray[i] << "  " << crossoverProbability << endl;
        if(_crossoverProbabilityArray[i] < crossoverProbability) {
            unsigned num = taskNum/carNum;
            int indexOf = rand()%num;
            //cout << "enter crossover  " << i << "  " << indexOf << endl;
            vector<Chromosome> chromosomeArr =
                    crossover(_chromosomeSet[i], _chromosomeSet[i+1], indexOf);
            _chromosomeSet.push_back(chromosomeArr[0]);
            _chromosomeSet.push_back(chromosomeArr[1]);
        }
    }
}

void GeneticAlgorithm::mutateChromosome() {
    int ChromosomePopulation = _chromosomeSet.size();
    //cout << ChromosomePopulation << endl;
    for(int i = 0; i < ChromosomePopulation; i++) {
        //cout << "mutate  " << i << endl;
        //cout << _mutateProbabilityArray[i] << " " << mutateProbability << endl;
        if(_mutateProbabilityArray[i] < mutateProbability) {
            //cout << "mutate  " << i << endl;
            //_chromosomeSet[i].printGenes();
            _chromosomeSet.push_back(mutate(_chromosomeSet[i]));
        }
    }
}
