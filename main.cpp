//#include "mainwindow.h"
//#include <QApplication>
#include "task.h"
#include "graph.h"
#include "geneticalgorithm.h"

int main(int argc, char *argv[]) {
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
    Graph G("C:\\Users\\10761\\Documents\\AGV_System\\map\\vers.txt",
            "C:\\Users\\10761\\Documents\\AGV_System\\map\\matrix.txt");
    G.run();
    TaskSet tSet("C:\\Users\\10761\\Documents\\AGV_System\\map\\tasks.txt");
    CarSet cSet;
    GeneticAlgorithm GA(cSet, tSet, G);
    GA.run();
    //cout << "end" << endl;
    return 0;
}
