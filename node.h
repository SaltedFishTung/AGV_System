#ifndef NODE_H
#define NODE_H

class Node {
public:
    int G;              // G：是个准确的值，是起点到当前结点的代价
    int H;	            // H：是个估值，当前结点到目的结点的估计代价
    Node *parent;       // 父节点
    Node(int id);
    Node(const Node& node);
    Node(int id, Node& node, int g, int h);
    bool operator <(const Node& node);
private:
    int _id;            // 节点编号
};

#endif // NODE_H
