#ifndef CROSSROAD_H
#define CROSSROAD_H

#include<QObject>
#include<QTimer>

#include"crossroadpainter.h"

class TrafficLight;

class CrossRoad : public QObject
{
    Q_OBJECT
public:
  CrossRoad(Road* left_road,
            Road* top_road,
            Road* right_road,
            Road* bottom_road);

  void setCrossRoadPainter(CrossRoadPainter& painter);

  void setTrafficLight(const TrafficLight* traffic_light);

  long getPrimaryRouteRaiting() const;
  long getSecondaryRouteRaiting() const;

public slots:
  void timerTick();

  void primaryAllowedToCross(bool& allowed);
  void secondaryAllowedToCross(bool& allowed);

  void generateLeftCar();
  void generateTopCar();
  void generateRightCar();
  void generateBottomCar();


private:
  Road* left_road;
  Road* top_road;
  Road* right_road;
  Road* bottom_road;
  const TrafficLight* traffic_light;

  QTimer* left_generator = new QTimer();
  QTimer* right_generator = new QTimer();
  QTimer* top_generator = new QTimer();
  QTimer* bottom_generator = new QTimer();
};

#endif // CROSSROAD_H
