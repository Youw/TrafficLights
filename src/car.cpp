#include "car.h"

Car::Car(float length, float width):
    my_length(length),
    my_width(width)
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
