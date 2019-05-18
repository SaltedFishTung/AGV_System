#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setMinimumSize(1600,900);
    setMaximumSize(1600,900);
    setAutoFillBackground(true);
    setPalette(QPalette(QColor(42, 42, 42)));
    timeId = startTimer(200);
}

MainWindow::~MainWindow(){}

void MainWindow::setMapModel(const string& versFilePath, const string& matrixFilePath) {
    mapModel.setModel(versFilePath, matrixFilePath);
}

void MainWindow::setCarGroupModel(const string &carsFilePath) {
    cGroupModel.setCarArr(carsFilePath);
}

void MainWindow::setTimeWindowGroup(const vector<TimeWindowsByCar> &twGroup) {
    for(const TimeWindowsByCar& twByCar : twGroup) {
        vector<int> points;
        for(const TimeWindow& tw : twByCar) {
            int point;
            if(tw.getDirection())
                point = mapModel.getEdgeStart(tw.getEdgeID());
            else
                point = mapModel.getEdgeEnd(tw.getEdgeID());
            points.push_back(point);
        }
        if(twByCar.back().getDirection())
            points.push_back(mapModel.getEdgeEnd(twByCar.back().getEdgeID()));
        else
            points.push_back(mapModel.getEdgeStart(twByCar.back().getEdgeID()));
        pointsSet.push_back(points);
        driftsOfX.push_back(0);
        driftsOfY.push_back(0);
        twGroupIndex.push_back(0);
    }
    for(const TimeWindowsByCar& twByCar : twGroup) {
        TimeWindowsByCar::const_iterator iter = twByCar.begin();
        vector<TimeWindow> twVec;
        while (++iter != twByCar.end()) {
            twVec.push_back(*iter);
        }
        this->twGroup.push_back(twVec);
    }
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    // 画地图
    painter.setPen(QPen(Qt::white, 2));
    int offsetOfX = 350;
    int offsetOfY = 50;
    for(int i = 0; i < mapModel.getEdgeNum(); i++) {
        int point1 = mapModel.getEdgeStart(i);
        int point2 = mapModel.getEdgeEnd(i);
        painter.drawLine(
            mapModel.getPointX(point1)+offsetOfX, mapModel.getPointY(point1)+offsetOfY,
            mapModel.getPointX(point2)+offsetOfX, mapModel.getPointY(point2)+offsetOfY);
    }
    for(int i = 0; i < cGroupModel.size(); i++) {
        int driftLen = sqrt(driftsOfX[i]*driftsOfX[i] + driftsOfY[i]*driftsOfY[i]);
        int point1, point2;
        if(twGroupIndex[i] >= twGroup.size())
            continue;
        if(twGroup[i][twGroupIndex[i]].getDirection()) {
            point1 = mapModel.getEdgeStart(twGroup[i][twGroupIndex[i]].getEdgeID());
            point2 = mapModel.getEdgeEnd(twGroup[i][twGroupIndex[i]].getEdgeID());
        } else {
            point1 = mapModel.getEdgeEnd(twGroup[i][twGroupIndex[i]].getEdgeID());
            point2 = mapModel.getEdgeStart(twGroup[i][twGroupIndex[i]].getEdgeID());
        }
        int deltaX = mapModel.getPointX(point2) - mapModel.getPointX(point1);
        int deltaY = mapModel.getPointY(point2) - mapModel.getPointY(point1);
        int deltaLen = sqrt(deltaX*deltaX + deltaY*deltaY);
        if(driftLen >= deltaLen) {
            twGroupIndex[i]++;
            driftsOfX[i] = 0;
            driftsOfY[i] = 0;
            continue;
        }
        int centerX = mapModel.getPointX(point1)+offsetOfX;
        int centerY = mapModel.getPointY(point1)+offsetOfY;
        int lenth = cGroupModel[i].getLenth();
        int width = cGroupModel[i].getWidth();
        switch (i) {
        case 0:
            painter.setPen(QPen(Qt::red, 2));
            break;
        case 1:
            painter.setPen(QPen(Qt::yellow, 2));
            break;
        case 2:
            painter.setPen(QPen(Qt::blue, 2));
            break;
        case 3:
            painter.setPen(QPen(Qt::green, 2));
            break;
        }
        QRect rect(centerX + driftsOfX[i] - lenth,
                   centerY + driftsOfY[i] - width,
                   2*lenth, 2*width);
        painter.drawRect(rect);
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    for(int i = 0; i < cGroupModel.size(); i++) {
        int point1, point2;
        if(twGroup[i][twGroupIndex[i]].getDirection()) {
            point1 = mapModel.getEdgeStart(twGroup[i][twGroupIndex[i]].getEdgeID());
            point2 = mapModel.getEdgeEnd(twGroup[i][twGroupIndex[i]].getEdgeID());
        } else {
            point1 = mapModel.getEdgeEnd(twGroup[i][twGroupIndex[i]].getEdgeID());
            point2 = mapModel.getEdgeStart(twGroup[i][twGroupIndex[i]].getEdgeID());
        }
        int deltaX = mapModel.getPointX(point2) - mapModel.getPointX(point1);
        int deltaY = mapModel.getPointY(point2) - mapModel.getPointY(point1);
        driftsOfX[i] += deltaX /
            (twGroup[i][twGroupIndex[i]].getExitTime() - twGroup[i][twGroupIndex[i]].getEnterTime());
        driftsOfY[i] += deltaY /
            (twGroup[i][twGroupIndex[i]].getExitTime() - twGroup[i][twGroupIndex[i]].getEnterTime());
    }
    update();
}
