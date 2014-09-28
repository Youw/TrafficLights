#include "road.h"

Road::Road(float width, unsigned lines_in, unsigned lines_out):
    road_width(width),
    lines_in(lines_in),
    lines_out(lines_out)
{
}

float Road::width() const
{
    return road_width;
}

unsigned Road::linesIn() const
{
    return lines_in;
}

unsigned Road::linesOut() const
{
    return lines_out;
}

void Road::moveAllCars() {
//
}

void Road::generateCar() {
//
}
