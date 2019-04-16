#include "car.h"
#include <vector>
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
