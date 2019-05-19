#ifndef CAR_H
#define CAR_H

#include <vector>
#include <string>
using namespace std;

class Car {
public:
    int startId;
    int carId;
    int v;
    int l;
    Car(int startId, int carId, int v=2, int l=2) :
        startId(startId), carId(carId), v(v), l(l) {}
};


class CarSet : public vector<Car> {
public :
    CarSet();
    CarSet(const string& carsFilePath);
    ~CarSet() {}
};

#endif // CAR_H
