//suppose it will be contained by the crossroad (it's logical by the way)
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QObject>
#include <QTimer>
#include <QTextStream>

#include "fl/Headers.h"

class CrossRoad;

class TrafficLight : public QObject
{
    Q_OBJECT
    const long int WarningTime = 1000;
    const long int DefaultSignalPeriod = 5000; // current signal extra time if there aren't cars
public: //types:
    enum Route{         //this should be defined in the crossroad lieu of here
        ROUT_PRIMARY = 0,
        ROUT_SECONDARY
    };
    static enum Route OppositRoute(const enum Route route);
    enum RouteSignal{
        SIGNAL_PERMIT = 0,
        SIGNAL_WARNING,
        SIGNAL_PROHIBITION
    };
    static RouteSignal OppositSignal(const enum RouteSignal signal);
    enum ControllerType{
        FUZZY_CONTROL = 0,
        CRISP_CONTROL
    };

public: //methods:
    TrafficLight(CrossRoad* p_crossRoad = 0);
    ~TrafficLight();
    enum RouteSignal RouteSignal(enum Route r) const;

    bool SetConfig(int primaryRouteInterval, int secondaryRouteInterval);
    bool SetConfig(const QTextStream & is);
    bool Start(ControllerType c_type);
    void Stop();
signals:
    void SignalChanged();
private slots:
    void ConsiderChange();
private:
    void _turnSignal(enum Route route, enum RouteSignal routeSignal, long interval = 0);
    long _calculateInterval(long crispARouteRating, long crispBRouteRating);
    CrossRoad * crossRoad;
    QTimer timer;
    enum RouteSignal primaryRouteSignal, secondaryRouteSignal;
    ControllerType controllerType;
        //crisp controller:
    int primaryPermitInterval, secondaryPermitInterval;
    enum RouteSignal lastPrimaryRouteSignal;
        //fuzzy controller:
    fl::Engine * engine;
    fl::InputVariable * aRouteRating, * bRouteRating;
    fl::OutputVariable * nextSignalWhile;
    fl::RuleBlock * ruleBlock;
};

#endif // TRAFFICLIGHT_H
