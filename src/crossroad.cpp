#include "crossroad.h"

#include"trafficlight.h"
#include"road.h"
#include"loader.h"
#include"globalsettings.h"

#include<random>
#include<chrono>

#include<QDebug>

CrossRoad::CrossRoad(Road *left_road, Road *top_road, Road *right_road, Road *bottom_road):
  left_road(left_road),
  top_road(top_road),
  right_road(right_road),
  bottom_road(bottom_road)
{
  left_generator->setParent(this);
  right_generator->setParent(this);
  top_generator->setParent(this);
  bottom_generator->setParent(this);

  left_road->setParent(this);
  top_road->setParent(this);
  right_road->setParent(this);
  bottom_road->setParent(this);

  connect(left_road,SIGNAL(carWantToCrossRoad(bool&)),this,SLOT(primaryAllowedToCross(bool&)));
  connect(right_road,SIGNAL(carWantToCrossRoad(bool&)),this,SLOT(primaryAllowedToCross(bool&)));

  connect(top_road,SIGNAL(carWantToCrossRoad(bool&)),this,SLOT(secondaryAllowedToCross(bool&)));
  connect(bottom_road,SIGNAL(carWantToCrossRoad(bool&)),this,SLOT(secondaryAllowedToCross(bool&)));

  connect(left_generator,SIGNAL(timeout()),this,SLOT(generateLeftCar()));
  connect(right_generator,SIGNAL(timeout()),this,SLOT(generateRightCar()));
  connect(bottom_generator,SIGNAL(timeout()),this,SLOT(generateBottomCar()));
  connect(top_generator,SIGNAL(timeout()),this,SLOT(generateTopCar()));

  left_generator->start(10);
  right_generator->start(10);
  top_generator->start(10);
  bottom_generator->start(10);
}

void CrossRoad::setCrossRoadPainter(CrossRoadPainter& painter)
{
  painter.setLeftRoad(left_road);
  painter.setTopRoad(top_road);
  painter.setRightRoad(right_road);
  painter.setBottomRoad(bottom_road);
  painter.setTrafficLight(traffic_light);
}


long CrossRoad::getPrimaryRouteRaiting() const
{
  long res = 0;
  for(size_t i = 0; i < left_road->linesIn(); i++) {
      Road::CarsLine& line = left_road->getInCarsOnLine(i);
      for(auto car = line.begin(); car != line.end(); car++) {
          res += car->getTimeBeingBeforeTrafficLights();
        }
    }
  for(size_t i = 0; i < right_road->linesIn(); i++) {
      Road::CarsLine& line = right_road->getInCarsOnLine(i);
      for(auto car = line.begin(); car != line.end(); car++) {
          res += car->getTimeBeingBeforeTrafficLights();
        }
    }
  return res;
}

long CrossRoad::getSecondaryRouteRaiting() const
{
  long res = 0;
  for(size_t i = 0; i < top_road->linesIn(); i++) {
      Road::CarsLine& line = top_road->getInCarsOnLine(i);
      for(auto car = line.begin(); car != line.end(); car++) {
          res += car->getTimeBeingBeforeTrafficLights();
        }
    }
  for(size_t i = 0; i < bottom_road->linesIn(); i++) {
      Road::CarsLine& line = bottom_road->getInCarsOnLine(i);
      for(auto car = line.begin(); car != line.end(); car++) {
          res += car->getTimeBeingBeforeTrafficLights();
        }
    }
  return res;
}

void CrossRoad::setTrafficLight(const TrafficLight *t_l)
{
  traffic_light = t_l;
}

void CrossRoad::timerTick()
{
  left_road->moveAllCars();
  top_road->moveAllCars();
  right_road->moveAllCars();
  bottom_road->moveAllCars();
}

void CrossRoad::primaryAllowedToCross(bool& allowed) {
  allowed = traffic_light->RouteSignal(TrafficLight::ROUT_PRIMARY) == TrafficLight::SIGNAL_PERMIT;
}

void CrossRoad::secondaryAllowedToCross(bool& allowed) {
  allowed = traffic_light->RouteSignal(TrafficLight::ROUT_SECONDARY) == TrafficLight::SIGNAL_PERMIT;
}

void CrossRoad::generateLeftCar() {
  left_generator->stop();
  Loader l;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution (GlobalSettings::time_to_next_car_primary,GlobalSettings::dispersion_time_next_car_primary);

  left_road->generateCar(l.cars.getImageLeft(l.cars.getRandomImageNum()));

  long how_long = std::abs(distribution(generator));
  qDebug() << "Left generated after:" << how_long << "ms";
  left_generator->start(how_long);
}

void CrossRoad::generateTopCar() {
  top_generator->stop();
  Loader l;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution (GlobalSettings::time_to_next_car_secondary,GlobalSettings::dispersion_time_next_car_secondary);

  top_road->generateCar(l.cars.getImageTop(l.cars.getRandomImageNum()));

  long how_long = std::abs(distribution(generator));
  qDebug() << "Top generated after:" << how_long << "ms";
  top_generator->start(how_long);
}

void CrossRoad::generateRightCar() {
  right_generator->stop();
  Loader l;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution (GlobalSettings::time_to_next_car_primary,GlobalSettings::dispersion_time_next_car_primary);

  right_road->generateCar(l.cars.getImageRight(l.cars.getRandomImageNum()));

  long how_long = std::abs(distribution(generator));
  qDebug() << "Right generated after:" << how_long << "ms";
  right_generator->start(how_long);
}

void CrossRoad::generateBottomCar() {
  bottom_generator->stop();
  Loader l;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution (GlobalSettings::time_to_next_car_secondary,GlobalSettings::dispersion_time_next_car_secondary);

  bottom_road->generateCar(l.cars.getImageBottom(l.cars.getRandomImageNum()));

  long how_long = std::abs(distribution(generator));
  qDebug() << "Bottom generated after:" << how_long << "ms";
  bottom_generator->start(how_long);
}
