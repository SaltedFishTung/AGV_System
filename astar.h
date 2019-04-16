#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <list>
using namespace std;

class Point
{
public:
    int x, y;           // 横纵坐标
    int F, G, H;        // F = G+H
    Point *parent;
    Point(int xx, int yy) : x(xx), y(yy), F(0), G(0), H(0), parent(nullptr) {}
};

class Astar
{
public:
    void InitAstar(vector<vector<int>> &_maze);
    list<Point *> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);

private:
    Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
    bool isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断
    Point *isInList(const list<Point *> &list, const Point *point) const; //判断开启/关闭列表中是否包含某点
    Point *getLeastFpoint(); //从开启列表中返回F值最小的节点
    //计算FGH值
    int calcG(Point *temp_start, Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);
private:
    vector<vector<int>> maze;
    list<Point *> openList;  //开启列表
    list<Point *> closeList; //关闭列表
};

#endif // ASTAR_H
