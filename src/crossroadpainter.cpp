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
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setRightRoad(const Road* road) {
  right_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setTopRoad(const Road* road) {
  top_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setBottomRoad(const Road* road) {
  bottom_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::resizeEvent(QResizeEvent *) {
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
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

  p.setPen(pen);
  p.drawLines(road_double_lines);

  p.setPen(pen);
  p.drawLines(road_bounds);

  pen.setStyle(Qt::DashLine);
  p.setPen(pen);
  p.drawLines(road_dashes);

  pen.setStyle(Qt::SolidLine);
  pen.setWidth(3);
  p.setPen(pen);
  p.drawLines(road_stop_lines);
}

void CrossRoadPainter::calculateLinesChoords() {
  road_dashes.clear();
  road_double_lines.clear();

  //fucking magic...
  road_bounds = decltype(road_bounds){
    //top(L,R)
    QLine(width()/2-top_road->widthInMeters()*SCALE/2,0,width()/2-top_road->widthInMeters()*SCALE/2,height()/2-left_road->widthInMeters()*SCALE/2),
    QLine(width()/2+top_road->widthInMeters()*SCALE/2,0,width()/2+top_road->widthInMeters()*SCALE/2,height()/2-right_road->widthInMeters()*SCALE/2),

    //left(T,B)
    QLine(0,height()/2-left_road->widthInMeters()*SCALE/2,width()/2-top_road->widthInMeters()*SCALE/2,    height()/2-left_road->widthInMeters()*SCALE/2),
    QLine(0,height()/2+left_road->widthInMeters()*SCALE/2,width()/2-bottom_road->widthInMeters()*SCALE/2, height()/2+left_road->widthInMeters()*SCALE/2),

    //bottom(L,R)
    QLine(width()/2-bottom_road->widthInMeters()*SCALE/2,height(),width()/2-bottom_road->widthInMeters()*SCALE/2,height()/2+left_road->widthInMeters()*SCALE/2),
    QLine(width()/2+bottom_road->widthInMeters()*SCALE/2,height(),width()/2+bottom_road->widthInMeters()*SCALE/2,height()/2+right_road->widthInMeters()*SCALE/2),

    //right(T,B)
    QLine(width(),height()/2-right_road->widthInMeters()*SCALE/2,width()/2+top_road->widthInMeters()*SCALE/2,height()/2-right_road->widthInMeters()*SCALE/2),
    QLine(width(),height()/2+right_road->widthInMeters()*SCALE/2,width()/2+bottom_road->widthInMeters()*SCALE/2,height()/2+right_road->widthInMeters()*SCALE/2)


  };

  auto line = QLine(road_bounds[0].p1(),{road_bounds[0].x2(),std::min(road_bounds[0].y2(),road_bounds[1].y2())});

  for(unsigned i = 1; line = line.translated(top_road->lineWidthInMeters()*SCALE,0), i<top_road->linesIn(); i++) {
      road_dashes.push_back(line);
    }
  auto tmp = line.x1();

  line = QLine(road_bounds[1].p1(),{road_bounds[1].x2(),std::min(road_bounds[0].y2(),road_bounds[1].y2())});
  for(unsigned i = 1; line = line.translated(-top_road->lineWidthInMeters()*SCALE,0), i<top_road->linesOut(); i++) {
      road_dashes.push_back(line);
    }
  tmp = (line.x1()-tmp)/2;

  road_double_lines.push_back(line.translated(tmp-1,0));
  road_double_lines.push_back(line.translated(tmp-4,0));


  line = QLine(road_bounds[2].p1(),{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[2].y2()});
  for(unsigned i = 1; line = line.translated(0,left_road->lineWidthInMeters()*SCALE), i<left_road->linesIn(); i++) {
      road_dashes.push_back(line);
    }
  tmp = line.y1();

  line = QLine(road_bounds[3].p1(),{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[3].y2()});
  for(unsigned i = 1; line = line.translated(0,-left_road->lineWidthInMeters()*SCALE), i<left_road->linesOut(); i++) {
      road_dashes.push_back(line);
    }
  tmp = (tmp-line.y1())/2;

  road_double_lines.push_back(line.translated(0,tmp-2));
  road_double_lines.push_back(line.translated(0,tmp+1));

    line = QLine(road_bounds[4].p1(),{road_bounds[4].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())});
    for(unsigned i = 1; line = line.translated(bottom_road->lineWidthInMeters()*SCALE,0), i<bottom_road->linesIn(); i++) {
        road_dashes.push_back(line);
      }
    tmp = line.x1();

    line = QLine(road_bounds[5].p1(),{road_bounds[5].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())});
    for(unsigned i = 1; line = line.translated(-bottom_road->lineWidthInMeters()*SCALE,0), i<bottom_road->linesOut(); i++) {
        road_dashes.push_back(line);
      }
    tmp = (line.x1()-tmp)/2;

  road_double_lines.push_back(line.translated(tmp-1,0));
  road_double_lines.push_back(line.translated(tmp-4,0));

  line = QLine(road_bounds[6].p1(),{std::max(road_bounds[6].x2(),road_bounds[7].x2()),road_bounds[6].y2()});
  for(unsigned i = 1; line = line.translated(0,right_road->lineWidthInMeters()*SCALE), i<right_road->linesIn(); i++) {
      road_dashes.push_back(line);
    }
  tmp = line.y1();

  line = QLine(road_bounds[7].p1(),{std::max(road_bounds[6].x2(),road_bounds[7].x2()),road_bounds[7].y2()});
  for(unsigned i = 1; line = line.translated(0,-right_road->lineWidthInMeters()*SCALE), i<right_road->linesOut(); i++) {
      road_dashes.push_back(line);
    }
  tmp = (tmp-line.y1())/2;

  road_double_lines.push_back(line.translated(0,tmp-2));
  road_double_lines.push_back(line.translated(0,tmp+1));

  road_stop_lines = decltype(road_stop_lines) {
      {{road_bounds[0].x2(),std::min(road_bounds[0].y2(),road_bounds[1].y2())},{road_bounds[1].x2(),std::min(road_bounds[0].y2(),road_bounds[1].y2())}},
      {{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[2].y2()},{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[3].y2()}},
      {{road_bounds[4].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())},{road_bounds[5].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())}},
      {{std::max(road_bounds[6].x2(),road_bounds[7].x2()),road_bounds[6].y2()},{std::max(road_bounds[6].x2(),road_bounds[7].x2()),road_bounds[7].y2()}}
    };
}
