#ifndef LOADER_H
#define LOADER_H

#include "road.h"
#include "trafficlight.h"
#include "crossroad.h"

class Loader
{
    const long PRIMARY_ROUTE_PERMIT_INTERVAL = 5;   //seconds
    const long SECONDARY_ROUTE_PERMIT_INTERVAL = 3; //
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
    static TrafficLight* result = generateTrafficLight(cross_road);
    return *result;
  }

private:
  TrafficLight* generateTrafficLight(CrossRoad* cross_road) {
    TrafficLight* result = new TrafficLight(cross_road);
    result->SetConfig(PRIMARY_ROUTE_PERMIT_INTERVAL, SECONDARY_ROUTE_PERMIT_INTERVAL);
    return result;
  }

};

#endif // LOADER_H
