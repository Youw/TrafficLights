//suppose it will be contained by the crossroad (it's logical by the way)
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QObject>
#include <QTimer>
#include <QTextStream>

#include "crossroad.h"
#include "fl/Headers.h"

class TrafficLight : public QObject
{
    Q_OBJECT
    const int WarningTime = 10;
    const int DefaultSignalPeriod = 30;
public: //types:
    enum Route{         //this should be defined in the crossroad lieu of here
        ROUT_PRIMARY,
        ROUT_SECONDARY
    };
    enum RouteSignal{
        SIGNAL_PERMIT,
        SIGNAL_WARNING,
        SIGNAL_PROHIBITION
    };
public: //methods:
    explicit TrafficLight(CrossRoad* p_crossRoad = 0);
    ~TrafficLight(){}
    bool SetConfigurations(const QTextStream & is);
    RouteSignal RouteSignal(Route r) const {return SIGNAL_WARNING;}
    //int StatePeriod() const {return 0;}
signals:
    void Permission(Route r);   //
    void Warning();             //for a painter
private slots:
    void ConsiderChange(){}
private:
    CrossRoad * crossRoad;
    QTimer timer;
    enum RouteSignal primaryRouteSignal;
        //fuzzy controller:
    fl::Engine * engine;
    fl::InputVariable * primaryRating, * secondaryRating;
    fl::OutputVariable * nextSignalWhile;
    fl::RuleBlock * ruleBlock;
};

#endif // TRAFFICLIGHT_H
