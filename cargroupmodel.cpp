#include "cargroupmodel.h"
#include <iostream>
#include <sstream>
#include <fstream>

CarGroupModel::CarGroupModel(const string &carsFilePath) {
    ifstream inCars(carsFilePath);
    string line;
    while (getline(inCars, line)) {
        istringstream iss(line);
        string id, startPoint;
        getline(iss, id, ' ');
        getline(iss, startPoint, ' ');
        this->push_back(CarModel(stoi(id), stoi(startPoint)));
    }
}

void CarGroupModel::setCarArr(const string &carsFilePath) {
    ifstream inCars(carsFilePath);
    string line;
    while (getline(inCars, line)) {
        istringstream iss(line);
        string id, startPoint;
        getline(iss, id, ' ');
        getline(iss, startPoint, ' ');
        this->push_back(CarModel(stoi(id), stoi(startPoint)));
    }
}
