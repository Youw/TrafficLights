#include "crossroadpainter.h"

#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QLine>
#include<QVector>

#include<unordered_map>

#include "road.h"
#include "trafficlight.h"

float CrossRoadPainter::METER_TO_PIXEL_SCALE = 10;
//just shorter name:
#define SCALE METER_TO_PIXEL_SCALE

CrossRoadPainter::CrossRoadPainter(QWidget *parent): QWidget(parent)
{
}

void CrossRoadPainter::setLeftRoad(Road* road)
{
  left_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setRightRoad(Road *road)
{
  right_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setTopRoad(Road* road)
{
  top_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setBottomRoad(Road* road)
{
  bottom_road = road;
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::setTrafficLight(const TrafficLight* t_l) {
  traffic_light = t_l;
}

void CrossRoadPainter::repaintAll(QPainter &p)
{
  clearAll(p);
  paintRoads(p);
  paintCars(p);
  paintTrafficLight(p);
}

void CrossRoadPainter::clearAll(QPainter &p)
{
  p.fillRect(rect(),Qt::NoBrush);
}

void CrossRoadPainter::paintRoads(QPainter &p)
{
  if(!left_road || !right_road || !top_road || !bottom_road) {
      p.drawText(rect(),Qt::AlignCenter,"Not all roads are setted for this painter");
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

void CrossRoadPainter::paintCars(QPainter &p)
{
  for(size_t i = 0; i < left_road->linesIn(); i++) {
      for(auto car = left_road->getInCarsOnLine(i).begin(); car !=  left_road->getInCarsOnLine(i).end(); car++) {
          int y_offset = carOffsetFromRightInPixels(*left_road,i);
          int pix_wid = car->width()*SCALE;
          int pix_len = car->length()*SCALE;
          int car_pos = car->frontPos()*SCALE;
          p.drawImage(QRect(l_road.right-pix_len-car_pos,l_road.bottom-y_offset-pix_wid/2,pix_len,pix_wid),*car->image(),car->image()->rect());
        }
    }

    for(size_t i = 0; i < top_road->linesIn(); i++) {
        for(auto car = top_road->getInCarsOnLine(i).begin(); car !=  top_road->getInCarsOnLine(i).end(); car++) {
            int x_offset = carOffsetFromRightInPixels(*top_road,i);
            int pix_wid = car->width()*SCALE;
            int pix_len = car->length()*SCALE;
            int car_pos = car->frontPos()*SCALE;
            p.drawImage(QRect(t_road.left-pix_wid/2+x_offset,t_road.bottom-pix_len-car_pos,pix_wid,pix_len),*car->image(),car->image()->rect());
          }
      }

  for(size_t i = 0; i < right_road->linesIn(); i++) {
      for(auto car = right_road->getInCarsOnLine(i).begin(); car !=  right_road->getInCarsOnLine(i).end(); car++) {
          int y_offset = carOffsetFromRightInPixels(*right_road,i);
          int pix_wid = car->width()*SCALE;
          int pix_len = car->length()*SCALE;
          int car_pos = car->frontPos()*SCALE;
          p.drawImage(QRect(r_road.left+car_pos,r_road.top+y_offset-pix_wid/2,pix_len,pix_wid),*car->image(),car->image()->rect());
        }
    }

  for(size_t i = 0; i < bottom_road->linesIn(); i++) {
      for(auto car = bottom_road->getInCarsOnLine(i).begin(); car !=  bottom_road->getInCarsOnLine(i).end(); car++) {
          int x_offset = carOffsetFromRightInPixels(*bottom_road,i);
          int pix_wid = car->width()*SCALE;
          int pix_len = car->length()*SCALE;
          int car_pos = car->frontPos()*SCALE;
          p.drawImage(QRect(b_road.right-pix_wid/2-x_offset,b_road.top+car_pos,pix_wid,pix_len),*car->image(),car->image()->rect());
        }
    }
}

int CrossRoadPainter::carOffsetFromRightInPixels(const Road& road, unsigned road_line)
{
  return road.lineWidthInMeters()*SCALE*(road_line+0.5);
}

void CrossRoadPainter::paintTrafficLight(QPainter &p)
{
  if(!traffic_light) {
      p.drawText(rect(),Qt::AlignCenter,"Traffic light\n not setted\n for this painter");
      return;
    }

  paintTrafficLightAt(p,width()/2,height()/2,traffic_light_size_pixels,traffic_light_size_pixels);

  //дублюємо бульшу копію
  int size = std::min(width()/5,height()/5);
  int margin = std::min(width()*3/15,height()*3/15);
  paintTrafficLightAt(p,margin,height()-margin,size,size);

}

void CrossRoadPainter::paintTrafficLightAt(QPainter& p, int x, int y, int width,int height)
{
  static std::unordered_map<int,QColor> signal_to_color {
    {TrafficLight::SIGNAL_PERMIT,         QColor(Qt::green)},
    {TrafficLight::SIGNAL_WARNING,        QColor(Qt::yellow)},
    {TrafficLight::SIGNAL_PROHIBITION,    QColor(Qt::red)}
  };

  QPen pen;//(signal_to_color[ traffic_light->RouteSignal(TrafficLight::ROUT_PRIMARY) ]);
  QBrush brush(signal_to_color[ traffic_light->RouteSignal(TrafficLight::ROUT_PRIMARY) ]);
  p.setPen(pen);
  p.setBrush(brush);

  float light_margin = 7/2.0;

  p.drawEllipse(QPoint(x-width/light_margin,y),int(width/2.0),int(height/2.0));
  p.drawEllipse(QPoint(x+width/light_margin,y),int(width/2.0),int(height/2.0));

//  pen.setColor(signal_to_color[ traffic_light->RouteSignal(TrafficLight::ROUT_SECONDARY) ]);
  brush.setColor(signal_to_color[ traffic_light->RouteSignal(TrafficLight::ROUT_SECONDARY) ]);
//  p.setPen(pen);
  p.setBrush(brush);

  p.drawEllipse(QPoint(x,y-height/light_margin),int(width/2.0),int(height/2.0));
  p.drawEllipse(QPoint(x,y+height/light_margin),int(width/2.0),int(height/2.0));

//  p.setPen(QPen());
  p.setBrush(QBrush(Qt::black));
  p.drawRect(x-width/2.0,y-height/2.0,width,height);
}

void CrossRoadPainter::paintEvent(QPaintEvent*)
{
  QPainter p(this);
  repaintAll(p);
}

void CrossRoadPainter::resizeEvent(QResizeEvent *)
{
  if(left_road && right_road && top_road && bottom_road)
    calculateLinesChoords();
}

void CrossRoadPainter::calculateLinesChoords()
{
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
  road_double_lines.push_back(line.translated(tmp-2,0));
  road_double_lines.push_back(line.translated(tmp+1,0));


  line = QLine(road_bounds[2].p1(),{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[2].y2()});
  for(unsigned i = 1; line = line.translated(0,left_road->lineWidthInMeters()*SCALE), i<left_road->linesOut(); i++) {
      road_dashes.push_back(line);
    }
  tmp = line.y1();
  line = QLine(road_bounds[3].p1(),{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[3].y2()});
  for(unsigned i = 1; line = line.translated(0,-left_road->lineWidthInMeters()*SCALE), i<left_road->linesIn(); i++) {
      road_dashes.push_back(line);
    }
  tmp = (tmp-line.y1())/2;
  road_double_lines.push_back(line.translated(0,tmp-2));
  road_double_lines.push_back(line.translated(0,tmp+1));

  line = QLine(road_bounds[4].p1(),{road_bounds[4].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())});
  for(unsigned i = 1; line = line.translated(bottom_road->lineWidthInMeters()*SCALE,0), i<bottom_road->linesOut(); i++) {
      road_dashes.push_back(line);
    }
  tmp = line.x1();
  line = QLine(road_bounds[5].p1(),{road_bounds[5].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())});
  for(unsigned i = 1; line = line.translated(-bottom_road->lineWidthInMeters()*SCALE,0), i<bottom_road->linesIn(); i++) {
      road_dashes.push_back(line);
    }
  tmp = (line.x1()-tmp)/2;
  road_double_lines.push_back(line.translated(tmp-2,0));
  road_double_lines.push_back(line.translated(tmp+1,0));

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
      //top
      {{road_bounds[0].x2(),std::min(road_bounds[0].y2(),road_bounds[1].y2())},{road_bounds[1].x2(),std::min(road_bounds[0].y2(),road_bounds[1].y2())}},
      //left
      {{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[2].y2()},{std::min(road_bounds[2].x2(),road_bounds[3].x2()),road_bounds[3].y2()}},
      //bottom
      {{road_bounds[4].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())},{road_bounds[5].x2(),std::max(road_bounds[4].y2(),road_bounds[5].y2())}},
      //right
      {{std::max(road_bounds[6].x2(),road_bounds[7].x2()),road_bounds[6].y2()},{std::max(road_bounds[6].x2(),road_bounds[7].x2()),road_bounds[7].y2()}}

  };

  t_road = decltype(t_road) {
    road_stop_lines[0].y1(),
    road_stop_lines[0].x1()
  };

  l_road = decltype(l_road) {
    road_stop_lines[1].x1(),
    road_stop_lines[1].y2()
  };

  b_road = decltype(b_road) {
    road_stop_lines[2].y1(),
    road_stop_lines[2].x2()
  };

  r_road = decltype(r_road) {
    road_stop_lines[3].x1(),
    road_stop_lines[3].y1()
};


  traffic_light_size_pixels = 0.3*SCALE*std::min(std::min(left_road->widthInMeters(),top_road->widthInMeters()),
                                                 std::min(right_road->widthInMeters(),bottom_road->widthInMeters()));
}
