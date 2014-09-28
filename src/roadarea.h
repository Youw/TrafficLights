#ifndef ROADAREA_H
#define ROADAREA_H

#include "road.h"

#include<QWidget>

class RoadArea : public QWidget
{
    Q_OBJECT
public:
    static const float METER_TO_PIXEL_SCALE;

    explicit RoadArea(QWidget *parent = 0);

    virtual void paintEvent(QPaintEvent*) override;

public slots:
    void setLeftRoad(const Road* road);
    void setRightRoad(const Road* road);
    void setTopRoad(const Road* road);
    void setBottomRoad(const Road* road);

private:
    const Road* left_road = 0;
    const Road* right_road = 0;
    const Road* top_road = 0;
    const Road* bottom_road = 0;
};

#endif // ROADAREA_H
