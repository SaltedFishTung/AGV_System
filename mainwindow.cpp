#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    widget = new Widget(this);

}

MainWindow::~MainWindow()
{
   // delete ui;
}
