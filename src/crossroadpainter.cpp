#include "crossroadpainter.h"

#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QLine>
#include<QVector>

float CrossRoadPainter::METER_TO_PIXEL_SCALE = 7;

#define SCALE METER_TO_PIXEL_SCALE

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

    pen.setStyle(Qt::SolidLine);
    p.setPen(pen);

    //some magic...
    QVector<QLine> lines = {
      QLine(width()/2-top_road->widthInMeters()*SCALE/2,0,width()/2-top_road->widthInMeters()*SCALE/2,height()/2-left_road->widthInMeters()*SCALE/2),
      QLine(width()/2+top_road->widthInMeters()*SCALE/2,0,width()/2+top_road->widthInMeters()*SCALE/2,height()/2-right_road->widthInMeters()*SCALE/2),

      QLine(0,height()/2-left_road->widthInMeters()*SCALE/2,width()/2-top_road->widthInMeters()*SCALE/2,    height()/2-left_road->widthInMeters()*SCALE/2),
      QLine(0,height()/2+left_road->widthInMeters()*SCALE/2,width()/2-bottom_road->widthInMeters()*SCALE/2, height()/2+left_road->widthInMeters()*SCALE/2),

      QLine(width()/2-bottom_road->widthInMeters()*SCALE/2,height(),width()/2-bottom_road->widthInMeters()*SCALE/2,height()/2+left_road->widthInMeters()*SCALE/2),
      QLine(width()/2+bottom_road->widthInMeters()*SCALE/2,height(),width()/2+bottom_road->widthInMeters()*SCALE/2,height()/2+right_road->widthInMeters()*SCALE/2),

      QLine(width(),height()/2-left_road->widthInMeters()*SCALE/2,width()/2+top_road->widthInMeters()*SCALE/2,height()/2-right_road->widthInMeters()*SCALE/2),
      QLine(width(),height()/2+left_road->widthInMeters()*SCALE/2,width()/2+bottom_road->widthInMeters()*SCALE/2,height()/2+right_road->widthInMeters()*SCALE/2)


    };

    p.drawLines(lines);

}
