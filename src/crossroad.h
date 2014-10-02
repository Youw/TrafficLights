#ifndef CROSSROAD_H
#define CROSSROAD_H

#include<QObject>

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

public slots:
  void timerTick();

private:
  Road* left_road;
  Road* top_road;
  Road* right_road;
  Road* bottom_road;
  TrafficLight* traffic_light;
};

#endif // CROSSROAD_H
