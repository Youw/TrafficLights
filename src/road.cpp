#include "road.h"

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

unsigned Road::linesIn() const
{
    return lines_in.size();
}

unsigned Road::linesOut() const
{
    return lines_out.size();
}

void Road::moveAllCars() {
//
}

void Road::generateCar() {
//
}
