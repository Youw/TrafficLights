#include "trafficlight.h"

#include "crossroad.h"

enum TrafficLight::RouteSignal TrafficLight::OppositSignal(const enum RouteSignal signal)
{
    if (signal == SIGNAL_WARNING)
        return SIGNAL_WARNING;
    else
        return (SIGNAL_PERMIT == signal) ? SIGNAL_PROHIBITION : SIGNAL_PERMIT;
}
enum TrafficLight::Route TrafficLight::OppositRoute(const enum Route route)
{
    return (route == ROUT_PRIMARY) ? ROUT_SECONDARY : ROUT_PRIMARY;
}
TrafficLight::TrafficLight(CrossRoad* p_crossRoad) :
    QObject(p_crossRoad), crossRoad(p_crossRoad),
    primaryRouteSignal(SIGNAL_WARNING),
    secondaryRouteSignal(SIGNAL_WARNING),
    controllerType(CRISP_CONTROL),
    primaryPermitInterval(0),
    secondaryPermitInterval(0),
    lastPrimaryRouteSignal(SIGNAL_PROHIBITION),
    engine(NULL),
    primaryRating(NULL),
    secondaryRating(NULL),
    nextSignalWhile(NULL),
    ruleBlock(NULL)
{
    timer.setSingleShot(true);
}
TrafficLight::~TrafficLight()
{

}
void TrafficLight::_turnSignal(Route route, enum RouteSignal routeSignal, int interval)
{
    lastPrimaryRouteSignal = primaryRouteSignal;
    primaryRouteSignal = ((route == ROUT_PRIMARY) ? routeSignal : OppositSignal(routeSignal));
    secondaryRouteSignal = OppositSignal(primaryRouteSignal);
    if (interval)
        timer.start(interval);
    emit SignalChanged();
}
enum TrafficLight::RouteSignal TrafficLight::RouteSignal(enum Route r) const
{
    return (ROUT_PRIMARY == r) ? primaryRouteSignal : secondaryRouteSignal;
}
bool TrafficLight::SetConfig(int v_priPermitInterval, int v_secPermitInterval)
{
    if (!(v_priPermitInterval > 0 && v_secPermitInterval > 0))
        return false;
    primaryPermitInterval = v_priPermitInterval;
    secondaryPermitInterval = v_secPermitInterval;
    connect(&timer, SIGNAL(timeout()), this, SLOT(ConsiderChange()));
    controllerType = CRISP_CONTROL;
    return true;
}
bool TrafficLight::SetConfig(const QTextStream & is)
{
    (void)is;
    //fuzzy logic settings

    connect(&timer, SIGNAL(timeout()), this, SLOT(ConsiderChange()));
    controllerType = FUZZY_CONTROL;
    return true;
}
bool TrafficLight::Start(ControllerType c_type)
{
    if (c_type == CRISP_CONTROL)
    {
        if (!(primaryPermitInterval > 0 && secondaryPermitInterval > 0))
            return false;
    }else
    {
        if (!engine)
            return false;
    }
    ConsiderChange();
    return true;
}
void TrafficLight::Stop()
{
    timer.stop();
    _turnSignal(ROUT_PRIMARY, SIGNAL_WARNING);
}
void TrafficLight::ConsiderChange()//dessision about signal type and its while
{
    if (controllerType == CRISP_CONTROL)
    {
        int nextInterval;
        if (lastPrimaryRouteSignal == SIGNAL_WARNING)
            nextInterval = WarningTime;
        else if (lastPrimaryRouteSignal == SIGNAL_PERMIT)
            nextInterval = secondaryPermitInterval;
        else
            nextInterval = primaryPermitInterval;
        _turnSignal(ROUT_PRIMARY, OppositSignal(lastPrimaryRouteSignal), nextInterval);
    }
    else
    {

    }
    //QTimer::singleShot(600000, &app, SLOT(quit()));
}
