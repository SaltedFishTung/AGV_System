#include "mapinfo.h"
#include "node.h"
#include <list>
#include <queue>

MapInfo::MapInfo(File file) {

}

void MapInfo::_Dijkstra(int source) {       // source为源点
    list<Node> S;                           // 存储最终结果
    priority_queue<Node> Q;                 // 优先队列
    list<Node> nodes;                       // 存储中间结果
    // 初始化
    for(int i = 0; i < _graph.size(); i++) {
        Node node = new Node(i, INT_MAX);
        nodes.push_back(node);
        if(i == source) {
            node.d = 0;
            Q.push(node);
        }
    }
    // 填写图上所有点到源点的最短距离
    while(Q.size() > 0) {
        Node u = Q.pop();
        S.push_back(u);
        for(int v = 0; v < _graph.size(); v++) {
            if(_graph[u.s][v] != INT_MAX && nodes.get(v).d > u.d+_graph[u.s][v]) {
                Node node = nodes.get(v);
                node.d = u.d+_graph[u.s][v];
                Q.pop();
                Q.push(node);
                _dijstra[source][v] = u.s;
            }
        }
    }
}
