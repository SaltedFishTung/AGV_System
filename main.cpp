#include <QApplication>
#include <QPropertyAnimation>
#include "mainwindow.h"
#include "task.h"
#include "graph.h"
#include "geneticalgorithm.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    Graph G("C:\\Users\\10761\\Documents\\AGV_System\\map\\vers.txt",
            "C:\\Users\\10761\\Documents\\AGV_System\\map\\matrix.txt");
    TaskSet tSet("C:\\Users\\10761\\Documents\\AGV_System\\map\\tasks.txt");
    CarSet cSet;
    GeneticAlgorithm GA(cSet, tSet, G);
    GA.run();
    w.setMapModel("C:\\Users\\10761\\Documents\\AGV_System\\map\\vers.txt",
                  "C:\\Users\\10761\\Documents\\AGV_System\\map\\matrix.txt");
    w.setCarGroupModel("C:\\Users\\10761\\Documents\\AGV_System\\map\\cars.txt");
    w.setTimeWindowGroup(GA.getResultPath());
    w.show();
    return a.exec();
}
