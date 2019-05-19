#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <string>
#include "pointgroupmodel.h"
#include "edgegroupmodel.h"
using namespace std;

class MapModel
{
public:
    MapModel() { }
    MapModel(const string& versFilePath, const string& matrixFilePath);

    int getPointNum() const { return pGroupModel.size(); }
    int getEdgeNum() const { return eGroupModel.size(); }
    int getEdgeStart(int id) const { return eGroupModel[id-1].getStart(); }
    int getEdgeEnd(int id) const { return eGroupModel[id-1].getEnd(); }
    int getPointX(int id) const { return pGroupModel[id-1].getX(); }
    int getPointY(int id) const { return pGroupModel[id-1].getY(); }

    void setModel(const string& versFilePath, const string& matrixFilePath);
private:
    PointGroupModel pGroupModel;
    EdgeGroupModel eGroupModel;
};

#endif // MAPMODEL_H
