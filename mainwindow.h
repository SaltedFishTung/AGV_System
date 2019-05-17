#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <string>
#include "mapmodel.h"
#include "cargroupmodel.h"
using namespace std;

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    void setMapModel(const string& versFilePath, const string& matrixFilePath);
    void setCarGroupModel(const string& carsFilePath);

    void paintEvent(QPaintEvent*);
private:
    MapModel mapModel;
    CarGroupModel cGroupModel;
};

#endif // MAINWINDOW_H
