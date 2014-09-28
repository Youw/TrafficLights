#ifndef ROADAREA_H
#define ROADAREA_H

#include "road.h"

#include<QWidget>

class CrossRoadPainter : public QWidget
{
    Q_OBJECT
public:
    static float METER_TO_PIXEL_SCALE;

    explicit CrossRoadPainter(QWidget *parent = 0);

    virtual void paintEvent(QPaintEvent*) override;

    void setLeftRoad(const Road* road);
    void setRightRoad(const Road* road);
    void setTopRoad(const Road* road);
    void setBottomRoad(const Road* road);

    virtual void resizeEvent(QResizeEvent *) override;

private:    
    const Road* left_road = 0;
    const Road* right_road = 0;
    const Road* top_road = 0;
    const Road* bottom_road = 0;

    void calculateLinesChoords();
    QVector<QLine> road_bounds;
    QVector<QLine> road_dashes;
    QVector<QLine> road_double_lines;
    QVector<QLine> road_stop_lines;
};

#endif // ROADAREA_H
