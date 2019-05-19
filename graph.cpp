#include "graph.h"
#include <queue>
#include <vector>
#include <cstdlib>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
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
    _edgeId = new int*[getVerNum()];
    for(int v = 0; v < getVerNum(); v++) {
        _graph[v] = new int[getVerNum()];
        _distance[v] = new int[getVerNum()];
        _path[v] = new int[getVerNum()];
        _edgeId[v] = new int[getVerNum()];
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
            _edgeId[v][u] = -1;
            if(v == u)
                _distance[v][u] = 0;
            u++;
            if(u >= getVerNum())
                break;
        }
    }
    _edgeNum = 0;
    for(int i = 0; i < getVerNum(); i++) {
        for(int j = i+1; j < getVerNum(); j++)
            if(_graph[i][j] != -1) {
                _edgeId[i][j] = ++_edgeNum;
                _edgeId[j][i] = _edgeId[i][j];
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
    _edgeId = new int*[getVerNum()];
    for(int v = 0; v < getVerNum(); v++) {
        _graph[v] = new int[getVerNum()];
        _distance[v] = new int[getVerNum()];
        _path[v] = new int[getVerNum()];
        _edgeId[v] = new int[getVerNum()];
    }
    for(int v = 0; v < getVerNum(); v++) {
        for(int u = 0; u < getVerNum(); u++) {
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
        }
    }
    _edgeNum = 0;
    for(int i = 0; i < getVerNum(); i++) {
        for(int j = 0; j < i; j++)
            if(_graph[i][j] != -1) {
                _edgeId[i][j] = ++_edgeNum;
                _edgeId[j][i] = _edgeId[i][j];
            }
    }
}

Graph::Graph(const Graph &G) {
    for(auto ver : G._vertices) {
        _vertices.push_back(ver);
    }
    _graph = new int*[getVerNum()];
    _distance = new int*[getVerNum()];
    _path = new int*[getVerNum()];
    _edgeId = new int*[getVerNum()];
    for(int v = 0; v < getVerNum(); v++) {
        _graph[v] = new int[getVerNum()];
        _distance[v] = new int[getVerNum()];
        _path[v] = new int[getVerNum()];
        _edgeId[v] = new int[getVerNum()];
    }
    for(int i = 0; i < getVerNum(); i++) {
        for(int j = 0; j < getVerNum(); j++) {
            _graph[i][j] = G._graph[i][j];
            _distance[i][j] = G._distance[i][j];
            _edgeId[i][j] = G._edgeId[i][j];
        }
    }
    _edgeNum = G._edgeNum;
}

Graph::Graph(const Graph &G, int s, int e) {
    for(auto ver : G._vertices) {
        _vertices.push_back(ver);
    }
    _graph = new int*[getVerNum()];
    _distance = new int*[getVerNum()];
    _path = new int*[getVerNum()];
    _edgeId = new int*[getVerNum()];
    for(int v = 0; v < getVerNum(); v++) {
        _graph[v] = new int[getVerNum()];
        _distance[v] = new int[getVerNum()];
        _path[v] = new int[getVerNum()];
        _edgeId[v] = new int[getVerNum()];
    }
    for(int i = 0; i < getVerNum(); i++) {
        for(int j = 0; j < getVerNum(); j++) {
            _graph[i][j] = G._graph[i][j];
            _edgeId[i][j] = G._edgeId[i][j];
            _distance[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    _resumeEdgeSet.push_back(_graph[s][e]);
    _resumeStartSet.push_back(s);
    _resumeEndSet.push_back(e);
    _graph[s][e] = _graph[e][s] = -1;
    _edgeNum = G._edgeNum;
}

Graph::~Graph() {
    for(int v = 0; v < getVerNum(); v++) {
        delete[] _graph[v];
        delete[] _distance[v];
        delete[] _path[v];
        delete[] _edgeId[v];
    }
    delete[] _graph;
    delete[] _distance;
    delete[] _path;
    delete[] _edgeId;
}

void Graph::run() {
    for(int v = 0; v < getVerNum(); v++)
        Dijstra(v);
    setPathInfo();
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
        }
    }
}

int Graph::getShortestDist(int s, int e) const {
    return _distance[s][e];
}

vector<int> Graph::getShortestPath(int s, int e) const {
    vector<int> path;
    //cout << "in: " << s << "  " << e << "  size: ";
    while(s != e) {
        if(s < 0 || s > getVerNum())
            throw "can't find path";
        path.push_back(s);
        s = _path[s][e];
    }
    path.push_back(e);
    //cout << path.size() << endl;
    return path;
}

int Graph::getEdgeNum() const {
    return _edgeNum;
}

int Graph::getBeforeS(int s, int edgeToS) const {
    for(int i = 0; i < getVerNum(); i++)
        if(_edgeId[i][s] == edgeToS)
            return i;
}

bool Graph::isAlone(int s) const {
    for(int i = 0; i < getVerNum(); i++)
        if(_graph[s][i] != -1 && s != i)
            return false;
    return true;
}

void Graph::Dijstra(int s) {
    // 优先队列，最小堆，每次弹出当前最短距离的点
    priority_queue<Dist, vector<Dist>, greater<Dist>> Q;
    int add[getVerNum()];
    for(int i = 0; i < getVerNum(); i++)
        add[i] = 0;
    // 初始化
    Q.push(Dist(s, 0));
    while(!Q.empty()) {
        Dist dist = Q.top();
        Q.pop();
        add[dist.ver] = 1;
        for(int v = 0; v < getVerNum(); v++) {
            if(_graph[dist.ver][v] != -1 && add[v]==0 &&
               _distance[s][v] > dist.distance+_graph[dist.ver][v]) {
                _distance[s][v] = dist.distance+_graph[dist.ver][v];
                Q.push(Dist(v, _distance[s][v]));
                _path[v][s] = dist.ver;
            }
        }
    }
}

void Graph::removeEdge(int s, int e) {
    _graph[s][e] = _graph[e][s] = -1;
    for(int i = 0; i < getVerNum(); i++) {
        for(int j = 0; j < getVerNum(); j++) {
            if(i == j)
                _distance[i][j] = 0;
            else
                _distance[i][j] = INT_MAX;
        }
    }
}

void Graph::resume() {
    if(_resumeEdgeSet.empty())
        return;
    for(int i = 0; i < _resumeEdgeSet.size(); i++) {
        _graph[_resumeStartSet[i]][_resumeEndSet[i]]
            =_graph[_resumeEndSet[i]][_resumeStartSet[i]]
            =_resumeEdgeSet[i];
    }
    _resumeEdgeSet.clear();
    _resumeStartSet.clear();
    _resumeEndSet.clear();
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
    cout << e << " ";
    do {
        cout << _path[c][s] << "  ";
        c = _path[c][s];
    }while(_path[c][s] != s);
    cout << s << endl;
}

void Graph::printEdgeInfo() const {
    for(int i = 0; i < getVerNum(); i++) {
        for(int j = 0; j < getVerNum(); j++) {
            if(_edgeId[i][j] != -1)
                cout << "edge " << _edgeId[i][j] << ": "
                     << i << " " << j << endl;
        }
    }
}

void Graph::setPathInfo() {
    for(int i = 0; i < getVerNum(); i++) {
        vector<vector<int>> iTojPath;
        for(int j = 0; j < getVerNum(); j++) {
            iTojPath.push_back(getShortestPath(i, j));
        }
        _pathInfo.push_back(iTojPath);
    }
}
