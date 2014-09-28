#ifndef ROAD_H
#define ROAD_H

#include<vector>
#include<list>

#include<QObject>

#include"car.h"

class Road: public QObject
{
    Q_OBJECT

public:
    Road(unsigned lines_in, unsigned lines_out, float lineWidth);

    float widthInMeters() const;

    unsigned linesIn() const;
    unsigned linesOut() const;

signals:
    void carWantToCrossRoad(bool &allow_cross);

public slots:
    void moveAllCars();
    void generateCar();

private:
    float line_width;

    using RoadLine = std::list<Car>;

    std::vector<RoadLine> lines_in;
    std::vector<RoadLine> lines_out;

};

#endif // ROAD_H
