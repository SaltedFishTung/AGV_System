#include "edgegroupmodel.h"
#include <iostream>
#include <fstream>
#include <sstream>

EdgeGroupModel::EdgeGroupModel(const string& matrixFilePath) {
    ifstream inMatrix(matrixFilePath);
    string line;
    int v = 0, u = 0;
    int count = 0;
    while (getline(inMatrix, line)) {
        istringstream iss(line);
        string edge;
        ++v;
        u = 0;
        while(getline(iss, edge, ' ')) {
            ++u;
            int len = stoi(edge);
            if(v < u && len != -1)
                this->push_back(EdgeModel(v, u, len, ++count));
        }
    }
}

void EdgeGroupModel::setEdgeArr(const string &matrixFilePath) {
    ifstream inMatrix(matrixFilePath);
    string line;
    int v = 0, u = 0;
    int count = 0;
    while (getline(inMatrix, line)) {
        istringstream iss(line);
        string edge;
        ++v;
        u = 0;
        while(getline(iss, edge, ' ')) {
            ++u;
            int len = stoi(edge);
            if(v < u && len != -1)
                this->push_back(EdgeModel(v, u, len, ++count));
        }
    }
}
