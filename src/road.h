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

  float lineWidthInMeters() const;

  size_t linesIn() const;
  size_t linesOut() const;

signals:
  void carWantToCrossRoad(bool &allow_cross);
  void moveCarOutOfRoad(Car& car);

public slots:
  void moveAllCars();
  void generateCar(QImage *image);


public:
  using CarsLine = std::list<Car>;

  CarsLine& getInCarsOnLine(unsigned line_in);
  CarsLine& getOutCarsOnLine(unsigned line_out);

private:
  float line_width;

  std::vector<CarsLine> lines_in;
  std::vector<CarsLine> lines_out;

};

#endif // ROAD_H
