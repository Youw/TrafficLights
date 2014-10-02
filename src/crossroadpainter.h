#ifndef ROADAREA_H
#define ROADAREA_H

class Road;
class TrafficLight;

#include<QWidget>

class CrossRoadPainter : public QWidget
{
    Q_OBJECT
public:
  static float METER_TO_PIXEL_SCALE;

  explicit CrossRoadPainter(QWidget *parent = 0);


  void setLeftRoad(const Road* road);
  void setRightRoad(const Road* road);
  void setTopRoad(const Road* road);
  void setBottomRoad(const Road* road);
  void setTrafficLight(const TrafficLight* traffic_light);

  void clearAll(QPainter&p);
  void repaintAll(QPainter&p);
  void paintRoads(QPainter&p);
  void paintCars(QPainter&p);
  void paintTrafficLight(QPainter&p);

protected:
  virtual void paintEvent(QPaintEvent*) override;
  virtual void resizeEvent(QResizeEvent *) override;

private:    
  const Road* left_road = 0;
  const Road* right_road = 0;
  const Road* top_road = 0;
  const Road* bottom_road = 0;
  const TrafficLight* traffic_light = 0;

  void calculateLinesChoords();
  QVector<QLine> road_bounds;
  QVector<QLine> road_dashes;
  QVector<QLine> road_double_lines;
  QVector<QLine> road_stop_lines;

  int traffic_light_size_pixels = 0;

  void paintTrafficLightAt(QPainter& p, int x_center, int y_center, int width,int height);
};

#endif // ROADAREA_H
