#ifndef KSP_H
#define KSP_H

#include "graph.h"
#include<vector>
#include<queue>
using namespace std;

class Blen {
public:
    int index;
    int len;
    Blen(const Blen& b) : index(b.index), len(b.len) {}
    Blen(int i, int l) : index(i), len(l) {}
    ~Blen() {}
};
inline bool operator >(const Blen& arg1, const Blen& arg2) {
    return arg1.len > arg2.len;
}
inline bool operator <(const Blen& arg1, const Blen& arg2) {
    return arg1.len < arg2.len;
}

class KSP {
public:
    KSP(int K) : _K(K) {}
    //void run(int s, int e, const Graph& G);
private:
    vector<vector<int>> _A;       // 最短路径集合
    vector<int> _Alen;            // 最短路径长度
    vector<vector<int>> _B;       // 偏移路径集合
    priority_queue<Blen> _Blen;   // 偏移路径长度
    int _K;
    bool compareAEle(const vector<int>& arg1, const vector<int>& arg2);
    void find_B(const vector<int>& A, const Graph& G);
};

#endif // KSP_H
