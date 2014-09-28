#ifndef LOADER_H
#define LOADER_H

#include "road.h"

class Loader
{
public:
  Loader() {}

  Road* getLeftRoad() {
    return new Road(2,2,2.5);
  }

  Road* getTopRoad() {
    return new Road(2,1,2.5);
  }

  Road* getRightRoad() {
    return new Road(2,2,2.5);
  }

  Road* getBottomRoad() {
    return new Road(1,2,2.5);
  }

};

#endif // LOADER_H
