#ifndef LOADER_H
#define LOADER_H

#include "road.h"
#include "trafficlight.h"
#include "crossroad.h"

class Loader
{
public:
  Loader() {}

  Road* getLeftRoad() {
    static Road * result = new Road(2,2,2.5);
    return result;
  }

  Road* getTopRoad() {
    static Road * result = new Road(1,1,2.5);
    return result;
  }

  Road* getRightRoad() {
    static Road * result = new Road(2,2,2.5);
    return result;
  }

  Road* getBottomRoad() {
    static Road * result = new Road(1,1,2.5);
    return result;
  }

  TrafficLight& getTrafficLight(CrossRoad* cross_road) {
    static TrafficLight* result = new TrafficLight(cross_road);
    return *result;
  }

};

#endif // LOADER_H
