#include "crossroadpainter.h"

#include<QPainter>
#include<QPen>
#include<QBrush>

const float CrossRoadPainter::METER_TO_PIXEL_SCALE = 3;

CrossRoadPainter::CrossRoadPainter(QWidget *parent): QWidget(parent)
{
}

void CrossRoadPainter::setLeftRoad(const Road* road) {
    left_road = road;
}

void CrossRoadPainter::setRightRoad(const Road* road) {
    right_road = road;
}

void CrossRoadPainter::setTopRoad(const Road* road) {
    top_road = road;
}

void CrossRoadPainter::setBottomRoad(const Road* road) {
    bottom_road = road;
}

void CrossRoadPainter::paintEvent(QPaintEvent*) {
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
