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
    const int WarningTime = 10;
    const int DefaultSignalPeriod = 300;
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
    bool SetConfig(int priRouteInterval, int secRouteInterval);
    bool SetConfig(const QTextStream & is);
    bool Start(ControllerType c_type);
    void Stop();
signals:
    void SignalChanged();
private slots:
    void ConsiderChange();
private:
    void _turnSignal(enum Route route, enum RouteSignal routeSignal, int interval = 0);
    CrossRoad * crossRoad;
    QTimer timer;
    enum RouteSignal primaryRouteSignal, secondaryRouteSignal;
    ControllerType controllerType;
        //crisp controller:
    int primaryPermitInterval, secondaryPermitInterval;
    enum RouteSignal lastPrimaryRouteSignal;
        //fuzzy controller:
    fl::Engine * engine;
    fl::InputVariable * primaryRating, * secondaryRating;
    fl::OutputVariable * nextSignalWhile;
    fl::RuleBlock * ruleBlock;
};

#endif // TRAFFICLIGHT_H
