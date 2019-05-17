#ifndef POINTGROUPMODEL_H
#define POINTGROUPMODEL_H

#include <iostream>
#include <vector>
using namespace std;

class Point {
public:
    Point(int x, int y, int id) : x(x), y(y), id(id){}
    Point(const string &str);
    Point(const Point& p) : x(p.x), y(p.y), id(p.id) { }

    int getX() const { return x; }
    int getY() const { return y; }
    int getId() const { return id; }
private:
    int x;
    int y;
    int id;
};

class PointGroupModel : public vector<Point>{
public:
    PointGroupModel() { }
    PointGroupModel(const string& versFilePath);

    void setPointArr(const string& versFilePath);
};

#endif // POINTGROUPMODEL_H
