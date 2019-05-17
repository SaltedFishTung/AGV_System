#include "mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setMinimumSize(1600,900);
    setMaximumSize(1600,900);
    setAutoFillBackground(true);
    setPalette(QPalette(QColor(42, 42, 42)));
}

MainWindow::~MainWindow(){}

void MainWindow::setMapModel(const string& versFilePath, const string& matrixFilePath) {
    mapModel.setModel(versFilePath, matrixFilePath);
}

void MainWindow::setCarGroupModel(const string &carsFilePath) {
    cGroupModel.setCarArr(carsFilePath);
}

void MainWindow::paintEvent(QPaintEvent*) {
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
    // 画车
    for(int i = 0; i < cGroupModel.size(); i++) {
        int point = cGroupModel[i].getStartPoint();
        int centerX = mapModel.getPointX(point)+offsetOfX;
        int centerY = mapModel.getPointY(point)+offsetOfY;
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
        painter.drawLine(
                    centerX-lenth, centerY-width,
                    centerX+lenth, centerY-width);
        painter.drawLine(
                    centerX-lenth, centerY-width,
                    centerX-lenth, centerY+width);
        painter.drawLine(
                    centerX+lenth, centerY+width,
                    centerX+lenth, centerY-width);
        painter.drawLine(
                    centerX+lenth, centerY+width,
                    centerX-lenth, centerY+width);
    }
}
