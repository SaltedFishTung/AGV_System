#include <QApplication>
#include <QPropertyAnimation>
#include "mainwindow.h"
#include "task.h"
#include "graph.h"
#include "geneticalgorithm.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    Graph G("C:\\Users\\10761\\Documents\\AGV_System\\map\\\\vers\\vers-1.txt",
            "C:\\Users\\10761\\Documents\\AGV_System\\map\\matrix\\matrix-1.txt");
    TaskSet tSet("C:\\Users\\10761\\Documents\\AGV_System\\map\\tasks\\tasks-1.txt");
    CarSet cSet("C:\\Users\\10761\\Documents\\AGV_System\\map\\cars\\cars-1.txt");
    GeneticAlgorithm GA(cSet, tSet, G);
    GA.run();
    w.setMapModel("C:\\Users\\10761\\Documents\\AGV_System\\map\\vers\\vers-1.txt",
                  "C:\\Users\\10761\\Documents\\AGV_System\\map\\matrix\\matrix-1.txt");
    w.setCarGroupModel("C:\\Users\\10761\\Documents\\AGV_System\\map\\cars\\cars-1.txt");
    w.setTimeWindowGroup(GA.getResultPath());
    w.show();
    return a.exec();
}
