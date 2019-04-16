#ifndef CAR_H
#define CAR_H

#include <vector>
using namespace std;

class Car {
public:
    int verId;
    int carId;
    int v;
    int l;
    Car(int verId, int carId, int v=2, int l=2) :
        verId(verId), carId(carId), v(v), l(l) {}
};


class CarSet : public vector<Car> {
public :
    CarSet();
    ~CarSet() {}
};

#endif // CAR_H
