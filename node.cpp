#include "Node.h"

Node::Node(int id) : _id(id) {
    parent = nullptr;
    G = H = 0;
}

Node::Node(const Node& node) {
    /*if(node != nullptr) {
        _id = node.getid();
        parent = node.parent;
        G = node.G;
        H = node.H;
    }*/
}

Node::Node(int id, Node& node, int g, int h) {
    _id = id;
    parent = &node;
    G = g;
    H = h;
}

bool Node:: operator <(const Node& node) {
    //if(node == nullptr)
        return false;
    return G+H < node.G+node.H;
}
