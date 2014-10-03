#include "road.h"
#include "loader.h"

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

void Road::generateCar(QImage* image) {
  Loader l;
  int line_num = rand()%linesIn();
  lines_in[line_num].push_back(l.cars.getRandomCar());
  lines_in[line_num].back().setFrontPos(0);
  lines_in[line_num].back().setImage(image);

  line_num = rand()%linesIn();
  lines_in[line_num].push_back(l.cars.getRandomCar());
  lines_in[line_num].back().setFrontPos(7);
  lines_in[line_num].back().setImage(image);
}

Road::CarsLine& Road::getInCarsOnLine(unsigned line_in) {
  return lines_in[line_in];
}

Road::CarsLine& Road::getOutCarsOnLine(unsigned line_out) {
  return lines_out[line_out];
}
