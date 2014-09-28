#ifndef ROAD_H
#define ROAD_H

#include<QObject>

class Road: public QObject
{
    Q_OBJECT

public:
    Road(float width, unsigned lines_in, unsigned lines_out);

    float width() const;

    unsigned linesIn() const;
    unsigned linesOut() const;

signals:
    void carWantToCrossRoad(bool &allow_cross);

public slots:
    void moveAllCars();
    void generateCar();

private:
    float road_width;
    unsigned lines_in;
    unsigned lines_out;

};

#endif // ROAD_H
