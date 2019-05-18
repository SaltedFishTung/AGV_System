#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPoint>
#include <string>
#include <vector>
#include <QMouseEvent>
#include "mapmodel.h"
#include "cargroupmodel.h"
#include "timewindowsbycar.h"
using namespace std;

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    void setMapModel(const string& versFilePath, const string& matrixFilePath);
    void setCarGroupModel(const string& carsFilePath);
    void setTimeWindowGroup(const vector<TimeWindowsByCar>& twGroup);

    //绘图事件
    void paintEvent(QPaintEvent *event);
    //定时事件
    void timerEvent(QTimerEvent *event);
private:
    MapModel mapModel;
    CarGroupModel cGroupModel;
    vector<vector<int>> pointsSet;
    vector<vector<TimeWindow>> twGroup;
    vector<int> driftsOfX;
    vector<int> driftsOfY;
    vector<int> twGroupIndex;
    int timeId;
};

#endif // MAINWINDOW_H
