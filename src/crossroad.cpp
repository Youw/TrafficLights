#include "crossroad.h"

CrossRoad::CrossRoad(const Road &left_road, const Road &top_road, const Road &right_road, const Road &bottom_road):
  left_road(left_road),
  top_road(top_road),
  right_road(right_road),
  bottom_road(bottom_road)
{
}

void CrossRoad::timerTick() {

}

void CrossRoad::setPainter(CrossRoadPainter& painter) {
  painter.setLeftRoad(left_road);
  painter.setTopRoad(top_road);
  painter.setRightRoad(right_road);
  painter.setBottomRoad(bottom_road);
}
