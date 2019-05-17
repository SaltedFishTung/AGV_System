#ifndef EDGEGROUPMODEL_H
#define EDGEGROUPMODEL_H

#include <string>
#include <vector>
using namespace std;

class EdgeModel {
public:
    EdgeModel() { }
    EdgeModel(int v, int u, int len, int id) :
        start(v), end(u), len(len), id(id) { }
    EdgeModel(const EdgeModel& model) :
        start(model.start), end(model.end), len(model.len), id(model.id) { }

    int getStart() const { return start; }
    int getEnd() const { return end; }
    int getLen() const { return len; }
    int getId() const { return id; }
private:
    int start;
    int end;
    int len;
    int id;
};

class EdgeGroupModel : public vector<EdgeModel> {
public:
    EdgeGroupModel() { }
    EdgeGroupModel(const string& matrixFilePath);

    void setEdgeArr(const string& matrixFilePath);
};

#endif // EDGEGROUPMODEL_H
