#include "road.h"
#include "loader.h"
#include "globalsettings.h"
#include "random"

Road::Road(unsigned lines_in, unsigned lines_out, float lineWidth):
  line_width(lineWidth),
  lines_in(lines_in),
  lines_out(lines_out)
{
}

float Road::widthInMeters() const
{
  return line_width*(lines_in.size()+lines_out.size());
}

float Road::lineWidthInMeters() const
{
  return line_width;
}

size_t Road::linesIn() const
{
  return lines_in.size();
}

size_t Road::linesOut() const
{
  return lines_out.size();
}

void Road::moveAllCars() {

  for(size_t i = 0; i<lines_in.size(); i++) {
      CarsLine& line = lines_in[i];
      if(!line.size()) {
          continue;
        }
      float prew_car_back = -1;
      for(auto car = line.begin(); car != line.end(); ) {
          float new_pos = car->frontPos()-car->speed();
          if(prew_car_back>=0) {
              if(new_pos<prew_car_back) {
                  new_pos = prew_car_back;
                }
              car->setFrontPos(new_pos);
              prew_car_back = new_pos+car->length()+GlobalSettings::cars_distance;
            } else {
              if(new_pos>0) {
                  car->setFrontPos(new_pos);
                  prew_car_back = new_pos+car->length()+GlobalSettings::cars_distance;
                } else {
                  bool car_can_cross = false;
                  emit carWantToCrossRoad(car_can_cross);
                  if(car_can_cross) {
                      moveCarOutOfRoad(*car);
                      car = line.erase(car);
                      prew_car_back = -1;
                      continue;
                    } else {
                      car->setFrontPos(GlobalSettings::cars_distance);
                      prew_car_back = car->length()+2*GlobalSettings::cars_distance;
                    }
                }
            }
          car++;
        }
    }
}

void Road::generateCar(QImage* image) {
  Loader l;
  int line_num = rand()%linesIn();
  CarsLine& line = lines_in[line_num];
  Car& car = line.back();
  if(!line.size() || ((car.frontPos()+car.length())<GlobalSettings::default_distance_from_lights)) {
      line.push_back(l.cars.getRandomCar());
      line.back().setFrontPos(GlobalSettings::default_distance_from_lights);
      line.back().setImage(image);
    }
}

Road::CarsLine& Road::getInCarsOnLine(unsigned line_in) {
  return lines_in[line_in];
}

Road::CarsLine& Road::getOutCarsOnLine(unsigned line_out) {
  return lines_out[line_out];
}
