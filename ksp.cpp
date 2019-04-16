#include "ksp.h"
#include "graph.h"
#include <list>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

/*void KSP::run(int s, int e, const Graph& G) {
    // 初始化
    _A.push_back(G.getShortestPath(s, e));
    _Alen.push_back(G.getShortestDist(s, e));
    // 需要生成K条路径
    for(int k = 0; k < _K; i++) {
        for(int i = 0; i < _A[k].size()-1; i++) {
            // 以当前路径第i个节点为支点
            int spurNode = _A[k][i];
            // 生成已确定的根路径
            vector<int> rootPath(_A[k].begin(), _A[k].begin()+i);
            // 移除根路径之后的下一个节点
            for(auto Ae : _A)
                if(compareAEle(rootPath, vector<int>(Ae.begin(), Ae.begin()+i)))
                    G.removeEdge(Ae[i], Ae[i+1]);
            // 移除根路径中的所有点，防止形成环路
            for(auto node : rootPath)
                G.removeNode(node);
            vector<int>& totalPath = rootPath;
            vector<int> spurPath = G.Dijstra(spurNode, e);
            // 形成新路径
            totalPath.insert(totalPath.end(), spurPath.begin(), spurPath.end());
            _B.push_back(totalPath);
            // 恢复地图
            G.restore();
        }
        if(_B.empty())
            break;
        _A.push_back(_B[_Blen.top().index]);
        _B.erase(_B.begin()+_Blen.top().index);
        _Blen.pop();
    }
}
*/
bool KSP::compareAEle(const vector<int> &arg1, const vector<int> &arg2) {
    for(unsigned i = 0; i < arg1.size(); i++)
        if(arg1[i] != arg2[i])
            return false;
    return true;
}

void KSP::find_B(const vector<int> &A, const Graph &G) {

}

