#ifndef CARGROUPMODEL_H
#define CARGROUPMODEL_H

#define LENTH 15
#define WIDTH 10
#define VELOCITY 1

#include <string>
#include <vector>
using namespace std;

class CarModel {
public:
    CarModel() { }
    CarModel(int id, int startPoint) : id(id), startPoint(startPoint) {
        lenth = LENTH;
        width = WIDTH;
        velocity = VELOCITY;
    }

    int getId() const { return id; }
    int getStartPoint() const { return startPoint; }
    int getLenth() const { return lenth; }
    int getWidth() const { return width; }
    int getVelocity() const { return velocity; }
private:
    int id;
    int startPoint;
    int lenth;
    int width;
    int velocity;
};

class CarGroupModel : public vector<CarModel> {
public:
    CarGroupModel() { }
    CarGroupModel(const string& carsFilePath);

    void setCarArr(const string& carsFilePath);
};

#endif // CARGROUPMODEL_H
