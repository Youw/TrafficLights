#ifndef LOADER_H
#define LOADER_H

#include <QImage>

#include "road.h"
#include "trafficlight.h"
#include "crossroad.h"

class Loader
{

public:
  Loader() {}

  Road* getLeftRoad() {
    static Road * result = new Road(1,2,2.5);
    return result;
  }

  Road* getTopRoad() {
    static Road * result = new Road(3,1,2.5);
    return result;
  }

  Road* getRightRoad() {
    static Road * result = new Road(4,2,2.5);
    return result;
  }

  Road* getBottomRoad() {
    static Road * result = new Road(3,1,2.5);
    return result;
  }

  TrafficLight* getTrafficLight(CrossRoad* cross_road) {
    static TrafficLight* result = generateTrafficLight(cross_road);
    return result;
  }

  class Cars{
  public:

    unsigned getImagesCount() {
      return 5;
    }

    unsigned getRandomImageNum() {
      return rand()%getImagesCount();
    }

    QImage* getImageLeft(int car_index) {
      QImage* result;
      switch(car_index) {
        case 0: {
            static QImage *car_picture = new QImage(":/png/left/car-1.png");
            result = car_picture;
            break;
        }
        case 1: {
            static QImage *car_picture = new QImage(":/png/left/car-2.png");
            result = car_picture;
            break;
        }
        case 2: {
            static QImage *car_picture = new QImage(":/png/left/car-3.png");
            result = car_picture;
            break;
        }
        case 3: {
            static QImage *car_picture = new QImage(":/png/left/car-4.png");
            result = car_picture;
            break;
        }
        case 4: {
            static QImage *car_picture = new QImage(":/png/left/car-5.png");
            result = car_picture;
            break;
        }
        default:
          static QImage none;
          result = &none;
        }
      return result;
    }

    QImage* getImageTop(int car_index) {
      QImage* result;
      switch(car_index) {
        case 0: {
            static QImage *car_picture = new QImage(":/png/top/car-1.png");
            result = car_picture;
            break;
        }
        case 1: {
            static QImage *car_picture = new QImage(":/png/top/car-2.png");
            result = car_picture;
            break;
        }
        case 2: {
            static QImage *car_picture = new QImage(":/png/top/car-3.png");
            result = car_picture;
            break;
        }
        case 3: {
            static QImage *car_picture = new QImage(":/png/top/car-4.png");
            result = car_picture;
            break;
        }
        case 4: {
            static QImage *car_picture = new QImage(":/png/top/car-5.png");
            result = car_picture;
            break;
        }
        default:
          static QImage none;
          result = &none;
        }
      return result;
    }

    QImage* getImageRight(int car_index) {
      QImage* result;
      switch(car_index) {
        case 0: {
            static QImage *car_picture = new QImage(":/png/right/car-1.png");
            result = car_picture;
            break;
        }
        case 1: {
            static QImage *car_picture = new QImage(":/png/right/car-2.png");
            result = car_picture;
            break;
        }
        case 2: {
            static QImage *car_picture = new QImage(":/png/right/car-3.png");
            result = car_picture;
            break;
        }
        case 3: {
            static QImage *car_picture = new QImage(":/png/right/car-4.png");
            result = car_picture;
            break;
        }
        case 4: {
            static QImage *car_picture = new QImage(":/png/right/car-5.png");
            result = car_picture;
            break;
        }
        default:
          static QImage none;
          result = &none;
        }
      return result;
    }

    QImage* getImageBottom(int car_index) {
      QImage* result;
      switch(car_index) {
        case 0: {
            static QImage *car_picture = new QImage(":/png/bottom/car-1.png");
            result = car_picture;
            break;
        }
        case 1: {
            static QImage *car_picture = new QImage(":/png/bottom/car-2.png");
            result = car_picture;
            break;
        }
        case 2: {
            static QImage *car_picture = new QImage(":/png/bottom/car-3.png");
            result = car_picture;
            break;
        }
        case 3: {
            static QImage *car_picture = new QImage(":/png/bottom/car-4.png");
            result = car_picture;
            break;
        }
        case 4: {
            static QImage *car_picture = new QImage(":/png/bottom/car-5.png");
            result = car_picture;
            break;
        }
        default:
          static QImage none;
          result = &none;
        }
      return result;
    }

    Car getRandomCar() {
      return Car(3.5+(rand()%100/66.0),1.5+(rand()%100/160.0));
    }
  } cars;

private:
  TrafficLight* generateTrafficLight(CrossRoad* cross_road) {
    const long PRIMARY_ROUTE_PERMIT_INTERVAL = 5;   //seconds
    const long SECONDARY_ROUTE_PERMIT_INTERVAL = 3; //

    TrafficLight* result = new TrafficLight(cross_road);
    //result->SetConfig(PRIMARY_ROUTE_PERMIT_INTERVAL, SECONDARY_ROUTE_PERMIT_INTERVAL);
    result->SetConfig("settings.ini");
    //result->GenerateIni("settings.ini");
    return result;
  }

};

#endif // LOADER_H
