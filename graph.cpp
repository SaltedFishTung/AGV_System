#include "graph.h"
#include <queue>
#include <vector>
#include <cstdlib>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Graph::Graph(const string &versFilePath, const string &matrixFilePath) {
    ifstream inVers(versFilePath);
    ifstream inMatrix(matrixFilePath);
    string line;
    while(getline(inVers, line)) {
        _vertices.push_back(Vertex(line));
    }
    _graph = new int*[getVerNum()];
    _distance = new int*[getVerNum()];
    _path = new int*[getVerNum()];
    _resEdge = new int*[getVerNum()];
    for(int v = 0; v < getVerNum(); v++) {
        _graph[v] = new int[getVerNum()];
        _distance[v] = new int[getVerNum()];
        _path[v] = new int[getVerNum()];
        _resEdge[v] = new int[getVerNum()];
    }
    // 初始化邻接表
    for(int v = 0; v < getVerNum(); v++) {
        getline(inMatrix, line);
        istringstream iss(line);
        int u = 0;
        string edge;
        while(getline(iss, edge, ' ')) {
            _graph[v][u] = stoi(edge);
            _distance[v][u] = INT_MAX;
            if(v == u)
                _distance[v][u] = 0;
            u++;
            if(u >= getVerNum())
                break;
        }
    }
    inVers.close();
    inMatrix.close();
}

Graph::Graph(const vector<Vertex>& vers) {
    _vertices = vers;
    _graph = new int*[getVerNum()];
    _distance = new int*[getVerNum()];
    _path = new int*[getVerNum()];
    _resEdge = new int*[getVerNum()];
    for(int v = 1; v < getVerNum(); v++) {
        _graph[v] = new int[getVerNum()];
        _distance[v] = new int[getVerNum()];
        _path[v] = new int[getVerNum()];
        _resEdge[v] = new int[getVerNum()];
    }
    for(int v = 1; v < getVerNum(); v++) {
        for(int u = 1; u < getVerNum(); u++) {
            // 初始化邻接表
            if(getVer(v).x == getVer(u).x)
                _graph[v][u] = abs(getVer(v).y-getVer(u).y);
            else if(getVer(v).y == getVer(u).y)
                _graph[v][u] = abs(getVer(v).x-getVer(u).x);
            else
                _graph[v][u] = INT_MAX;
            // 初始化dist, path，res
            if(v == u) {
                _distance[v][u] = 0;
                _path[v][u] = 0;    // 0代表已到达
            }
            else {
                _distance[v][u] = INT_MAX;
                _path[v][u] = -1;   // -1代表仍未寻找
            }
            _resEdge[v][u] = -1;
        }
    }
}

Graph::~Graph() {
    for(int v = 0; v < getVerNum(); v++) {
        delete[] _graph[v];
        delete[] _distance[v];
        delete[] _path[v];
        delete[] _resEdge[v];
    }
    delete[] _graph;
    delete[] _distance;
    delete[] _path;
    delete[] _resEdge;
}

void Graph::run() {
    for(int v = 0; v < getVerNum(); v++)
        Dijstra(v);
    //Dijstra(0);
}

void Graph::init() {
    for(int v = 1; v < getVerNum(); v++) {
        for(int u = 1; u < getVerNum(); u++) {
            // 初始化邻接表
            if(getVer(v).x == getVer(u).x)
                _graph[v][u] = abs(getVer(v).y-getVer(u).y);
            else if(getVer(v).y == getVer(u).y)
                _graph[v][u] = abs(getVer(v).x-getVer(u).x);
            else
                _graph[v][u] = INT_MAX;
            // 初始化dist, path，res
            if(v == u) {
                _distance[v][u] = 0;
                _path[v][u] = 0;    // 0代表已到达
            }
            else {
                _distance[v][u] = INT_MAX;
                _path[v][u] = -1;   // -1代表仍未寻找
            }
            _resEdge[v][u] = -1;
        }
    }
}

int Graph::getShortestDist(int s, int e) const {
    return _distance[s][e];
}

vector<int> Graph::getShortestPath(int s, int e) const {
    vector<int> path;
    path.push_back(s);
    while(_path[s][e] != 0) {
        path.push_back(s);
        s = _path[s][e];
    }
    return path;
}

void Graph::removeEdge(int s, int e) {
    // 无向图，所以正反都要设置
    _resEdge[s][e] = _graph[s][e];
    _resEdge[e][s] = _graph[e][s];
    _graph[s][e] = INT_MAX;
    _graph[e][s] = INT_MAX;
}

void Graph::removeNode(int node) {
    for(int i = 1; i < getVerNum(); i++)
        if(_graph[i][node] != INT_MAX) {
            _resEdge[i][node] = _resEdge[node][i] = _graph[i][node];
            _graph[i][node] = _graph[node][i] = INT_MAX;
        }
}

void Graph::restore() {
    for(int v = 1; v < getVerNum(); v++) {
        for(int u = 1; u < getVerNum(); u++) {
            if(_resEdge[v][u] != -1)
                _graph[v][u] = _resEdge[v][u];
        }
    }
    for(int v = 1; v < getVerNum(); v++)
        memset(_resEdge[v], 0, sizeof(_resEdge[v])*getVerNum());
}

// 有待修改
void Graph::Dijstra(int s) {
    // 优先队列，最小堆，每次弹出当前最短距离的点
    priority_queue<Dist, vector<Dist>, greater<Dist>> Q;
    int add[getVerNum()];
    for(int i = 0; i < getVerNum(); i++)
        add[i] = 0;
    //cout << "----";
    //memset(add, 0, getVerNum()*sizeof(add));
    //cout << s << endl;

    // 初始化
    Q.push(Dist(s, 0));
    while(!Q.empty()) {
        Dist dist = Q.top();
        Q.pop();
        add[dist.ver] = 1;
        for(int v = 0; v < getVerNum(); v++) {
            //cout << s << "  " << dist.ver << "  " << v << "  " << _distance[s][v] << endl;
            //cout << _graph[dist.ver][v] << "  " << add[v] << "  " << _distance[s][v] <<
            //                         "  " << dist.distance+_distance[dist.ver][v] <<endl;
            if(_graph[dist.ver][v] != -1 && add[v]==0 &&
               _distance[s][v] > dist.distance+_graph[dist.ver][v]) {
                _distance[s][v] = dist.distance+_graph[dist.ver][v];
                Q.push(Dist(v, _distance[s][v]));
                _path[v][s] = dist.ver;
            }
        }
    }
}

void Graph::printGraph() const {
    for(int v = 0; v < getVerNum(); v++) {
        for(int u = 0; u < getVerNum(); u++)
            cout << _graph[v][u] << "  ";
        cout << endl;
    }
}

void Graph::printDist() const {
    for(int v = 0; v < getVerNum(); v++) {
        for(int u = 0; u < getVerNum(); u++)
            cout << _distance[v][u] << "  ";
        cout << endl;
    }
}

void Graph::printPath(int s, int e) const {
    int c = e;
    cout << e+1 << " ";
    do {
        cout << _path[c][s]+1 << "  ";
        c = _path[c][s];
    }while(_path[c][s] != s);
    cout << s+1 << endl;
}
