#include "car.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

CarSet::CarSet() {
    Car c1(1, 0);
    Car c2(5, 1);
    Car c3(9, 2);
    Car c4(13, 3);
    this->push_back(c1);
    this->push_back(c2);
    this->push_back(c3);
    this->push_back(c4);
}

CarSet::CarSet(const string &carsFilePath) {
    ifstream inCars(carsFilePath);
    string line;
    while (getline(inCars, line)) {
        istringstream iss(line);
        string id, startPoint;
        getline(iss, id, ' ');
        getline(iss, startPoint, ' ');
        this->push_back(Car(stoi(startPoint)-1, stoi(id)));
    }
}
