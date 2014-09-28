#include "crossroad.h"

CrossRoad::CrossRoad(Road *left_road, Road *top_road, Road *right_road, Road *bottom_road):
  left_road(left_road),
  top_road(top_road),
  right_road(right_road),
  bottom_road(bottom_road)
{
  left_road->setParent(this);
  top_road->setParent(this);
  right_road->setParent(this);
  bottom_road->setParent(this);
}

void CrossRoad::timerTick() {

}

void CrossRoad::setCrossRoadPainter(CrossRoadPainter& painter) {
  painter.setLeftRoad(left_road);
  painter.setTopRoad(top_road);
  painter.setRightRoad(right_road);
  painter.setBottomRoad(bottom_road);
}
