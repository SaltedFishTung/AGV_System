#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// (点，距离)的集合
class Dist {
public:
    Dist(int v, int d) : ver(v), distance(d) {}
    Dist(const Dist& d) { ver = d.ver; distance = d.distance; }
    int ver;
    int distance;
    Dist& operator =(const Dist& d) {
        ver = d.ver;
        distance = d.distance;
        return *this;
    }
    ~Dist() {
    }
};
inline bool operator >(const Dist& arg1, const Dist& arg2) {
    return arg1.distance > arg2.distance;
}

// 地图类，存储地图内的各项信息，以及处理最短距离
class Graph {
public:
    Graph(const string& versFilePath, const string& matrixFilePath);
    Graph(const Graph& G);
    Graph(const Graph &G, int s, int e);
    ~Graph();
    void run();                     // 遍历一遍，生成所有最短路径，完成初始化
    int getEdge(int s, int e) const { return _graph[s][e]; }
    int getEdgeId(int s, int e) const { return _edgeId[s][e]; }
    int getVerNum() const { return _verNum; }
    vector<int> getShortestPath(int s, int e) const;
    const vector<int>& getPathInfo(int s, int e) const { return _pathInfo[s][e]; }
    int getShortestDist(int s, int e) const;
    int getEdgeNum() const;
    int getBeforeS(int s, int edgeToS) const;
    bool isAlone(int s) const;
    void Dijstra(int s);
    void resume();
    void printGraph() const;
    void printDist() const;
    void printPath(int s, int e) const;
    void printEdgeInfo() const;
private:
    vector<vector<vector<int>>> _pathInfo;
    int** _graph;                   // 邻接矩阵
    int** _distance;                // 存储各点间的最短距离
    int** _path;                    // 存储最短距离的路径
    int** _edgeId;
    int _edgeNum;
    vector<int> _resumeStartSet;
    vector<int> _resumeEndSet;
    vector<int> _resumeEdgeSet;
    int _verNum;
    void setPathInfo();
};

#endif // GRAPH_H
