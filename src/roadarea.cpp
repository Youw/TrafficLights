#include "roadarea.h"

#include<QPainter>
#include<QPen>
#include<QBrush>

const float RoadArea::METER_TO_PIXEL_SCALE = 3;

RoadArea::RoadArea(QWidget *parent): QWidget(parent)
{
}

void RoadArea::setLeftRoad(const Road* road) {
    left_road = road;
}

void RoadArea::setRightRoad(const Road* road) {
    right_road = road;
}

void RoadArea::setTopRoad(const Road* road) {
    top_road = road;
}

void RoadArea::setBottomRoad(const Road* road) {
    bottom_road = road;
}

void RoadArea::paintEvent(QPaintEvent*) {
    QPainter p(this);

    p.fillRect(rect(),Qt::NoBrush);

    if(!left_road || !right_road || !top_road || !bottom_road) {
        p.drawText(rect(),Qt::AlignCenter,"Not all roads are setted for RoadArea");
        return;
    }

    QPen pen = QPen(QBrush(),2);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);

    p.setPen(pen);

    p.drawLine(10,10,100,100);


}
