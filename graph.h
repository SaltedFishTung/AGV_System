#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// 顶点类
class Vertex {
public:
    int x;
    int y;
    int id;
    Vertex(int x, int y, int id) : x(x), y(y), id(id){}
    Vertex(const string &str) {
        vector<int> sv;
        istringstream iss(str);
        string temp;
        while (getline(iss, temp, ' ')) {
            sv.push_back(stoi(temp));
        }
        x = sv[0];
        y = sv[1];
        id = sv[2];
    }
};

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
    Graph(const vector<Vertex>& vers);
    ~Graph();
    void init();
    void run();                     // 遍历一遍，生成所有最短路径，完成初始化

    Vertex getVer(int id) { return _vertices[id]; }
    int getEdge(int s, int e) { return _graph[s][e]; }
    void removeEdge(int s, int e);
    void removeNode(int node);
    void restore();
    int getVerNum() const { return _vertices.size(); }
    vector<int> getShortestPath(int s, int e) const;
    int getShortestDist(int s, int e) const;
    void Dijstra(int s);
    void printGraph() const;
    void printDist() const;
    void printPath(int s, int e) const;
private:
    vector<Vertex> _vertices;
    int** _graph;                   // 邻接矩阵
    int** _distance;                // 存储各点间的最短距离
    int** _path;                    // 存储最短距离的路径
    int** _resEdge;                 // 存储要恢复数据的边
};

#endif // GRAPH_H
