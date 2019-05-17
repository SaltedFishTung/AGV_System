#include "mapmodel.h"

MapModel::MapModel(const string& versFilePath, const string& matrixFilePath) :
    pGroupModel(versFilePath), eGroupModel(matrixFilePath) {
    //
}

void MapModel::setModel(const string &versFilePath, const string &matrixFilePath) {
    pGroupModel.setPointArr(versFilePath);
    eGroupModel.setEdgeArr(matrixFilePath);
}
