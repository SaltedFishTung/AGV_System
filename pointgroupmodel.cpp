#include "pointgroupmodel.h"
#include <vector>
#include <sstream>
#include <fstream>

Point::Point(const string &str) {
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

PointGroupModel::PointGroupModel(const string &versFilePath) {
    ifstream inVers(versFilePath);
    string line;
    while(getline(inVers, line)) {
        this->push_back(Point(line));
    }
}

void PointGroupModel::setPointArr(const string &versFilePath) {
    ifstream inVers(versFilePath);
    string line;
    while(getline(inVers, line)) {
        this->push_back(Point(line));
    }
}
