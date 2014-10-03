#ifndef ROADAREA_H
#define ROADAREA_H

class Road;
class TrafficLight;

#include<QWidget>

class CrossRoadPainter : public QWidget
{
    Q_OBJECT
public:
  explicit CrossRoadPainter(QWidget *parent = 0);


  void setLeftRoad(Road *road);
  void setRightRoad(Road* road);
  void setTopRoad(Road* road);
  void setBottomRoad(Road* road);
  void setTrafficLight(const TrafficLight* traffic_light);

  void clearAll(QPainter&p);
  void repaintAll(QPainter&p);
  void paintRoads(QPainter&p);
  void paintCars(QPainter&p);
  void paintTrafficLight(QPainter&p);

protected:
  static int carOffsetFromRightInPixels(const Road& road, unsigned road_line);

  virtual void paintEvent(QPaintEvent*) override;
  virtual void resizeEvent(QResizeEvent *) override;

private:    
  Road* left_road = 0;
  Road* right_road = 0;
  Road* top_road = 0;
  Road* bottom_road = 0;
  const TrafficLight* traffic_light = 0;

  void calculateLinesChoords();
  QVector<QLine> road_bounds;
  QVector<QLine> road_dashes;
  QVector<QLine> road_double_lines;
  QVector<QLine> road_stop_lines;

  int traffic_light_size_pixels = 0;

  void paintTrafficLightAt(QPainter& p, int x_center, int y_center, int width,int height);

  struct {
    int bottom;
    int left;
  } t_road;

  struct {
    int right;
    int bottom;
  } l_road;

  struct {
    int top;
    int right;
  } b_road;

  struct {
    int left;
    int top;
  } r_road;
};

#endif // ROADAREA_H
