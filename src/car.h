#ifndef CAR_H
#define CAR_H

class QImage;
#include<QDateTime>

class Car
{
public:
  Car(float length, float width);

  float width() const;
  float length() const;

  Car& setFrontPos(float pos);
  float frontPos() const;

  Car& setImage(QImage *image);
  QImage *image() const;

  float speed() const;

  time_t getTimeBeingBeforeTrafficLights() const;

private:
  float my_length;
  float my_width;

  float my_pos = 0;

  QImage *car_image = 0;

  time_t creation_time;
};

#endif // CAR_H
