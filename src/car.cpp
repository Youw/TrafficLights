#include "car.h"
#include "globalsettings.h"

#include <QPicture>

Car::Car(float length, float width):
  my_length(length),
  my_width(width),
  creation_time(QDateTime::currentDateTime().toTime_t())
{

}

float Car::length() const
{
  return my_length;
}

float Car::width() const
{
  return my_width;
}


Car& Car::setFrontPos(float pos) {
  my_pos = pos;
  return *this;
}

float Car::frontPos() const {
  return my_pos;
}

Car& Car::setImage(QImage *image) {
  car_image = image;
  return *this;
}

QImage *Car::image() const {
  return car_image;
}

float Car::speed() const {
  return GlobalSettings::default_car_speed/GlobalSettings::time_scale;
}

time_t Car::getTimeBeingBeforeTrafficLights() const {
  return QDateTime::currentDateTime().toTime_t()-creation_time;
}
