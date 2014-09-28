//suppose it will be contained by the crossroad (it's logical by the way)
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QObject>
#include <QTimer>

#include "crossroad.h"

class TrafficLight : public QObject
{
    Q_OBJECT
    const int WarningTime = 10;
    const int DefaultSignalPeriod = 30;
public:
    enum Route{         //this should be defined in the crossroad lieu of here
        ROUT_PRIMARY,
        ROUT_SECONDARY
    };
    enum RouteSignal{
        SIGNAL_PERMIT,
        SIGNAL_WARNING,
        SIGNAL_PROHIBITION
    };

    explicit TrafficLight(CrossRoad* p_crossRoad = 0);
    ~TrafficLight(){}
    RouteSignal RouteSignal(Route r) const {}
    int StatePeriod() const {return 0;}
signals:
    void Permission(Route r);   //
    void Warning();             //for a painter

private slots:
    void ConsiderChange(){}
private:
    QTimer m_timer;
};

#endif // TRAFFICLIGHT_H
