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
    aRouteRating(NULL),
    bRouteRating(NULL),
    nextSignalWhile(NULL),
    ruleBlock(NULL)
{
    timer.setSingleShot(true);
}
TrafficLight::~TrafficLight()
{

}
void TrafficLight::_turnSignal(Route route, enum RouteSignal routeSignal, long interval)
{
    interval *= MilisecondsPerSecond;
    lastPrimaryRouteSignal = primaryRouteSignal;
    primaryRouteSignal = ((route == ROUT_PRIMARY) ? routeSignal : OppositSignal(routeSignal));
    secondaryRouteSignal = OppositSignal(primaryRouteSignal);
    if (interval)
        timer.start(interval);
    emit SignalChanged();
}
long TrafficLight::_calculateInterval(long crispARouteRating, long crispBRouteRating)
{
    aRouteRating->setInputValue(crispARouteRating);
    bRouteRating->setInputValue(crispBRouteRating);
    engine->process();
    return nextSignalWhile->getOutputValue();
}
enum TrafficLight::RouteSignal TrafficLight::RouteSignal(enum Route r) const
{
    return (ROUT_PRIMARY == r) ? primaryRouteSignal : secondaryRouteSignal;
}
bool TrafficLight::SetConfig(int primaryRouteInterval, int secondaryRouteInterval)
{
    if (!(primaryRouteInterval > 0 && secondaryRouteInterval > 0))
        return false;
    primaryPermitInterval = primaryRouteInterval;
    secondaryPermitInterval = secondaryRouteInterval;
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
        long int nextInterval;
        if (lastPrimaryRouteSignal == SIGNAL_WARNING)
            nextInterval = WarningTime*MilisecondsPerSecond;
        else if (lastPrimaryRouteSignal == SIGNAL_PERMIT)
            nextInterval = secondaryPermitInterval;
        else
            nextInterval = primaryPermitInterval;
        _turnSignal(ROUT_PRIMARY, OppositSignal(lastPrimaryRouteSignal), nextInterval);
    }
    else
    {
        if (lastPrimaryRouteSignal == SIGNAL_WARNING)
        {
            _turnSignal(ROUT_PRIMARY, OppositSignal(lastPrimaryRouteSignal), nextSignalWhile->getOutputValue());
        }
        else
        {
            long int primaryCrispRating, secondaryCrispRating;
            primaryCrispRating = crossRoad->getPrimaryRouteRaiting();
            secondaryCrispRating = crossRoad->getSecondaryRouteRaiting();
            Route currentRoute = (primaryRouteSignal == SIGNAL_PERMIT) ? ROUT_PRIMARY : ROUT_SECONDARY;
            Route aRoute;
            if (primaryCrispRating == 0 && secondaryCrispRating != 0)
                aRoute = ROUT_SECONDARY;
            else if (primaryCrispRating != 0 && secondaryCrispRating == 0)
                aRoute = ROUT_PRIMARY;
            else if (primaryCrispRating != 0 && secondaryCrispRating != 0)
                aRoute = OppositRoute(currentRoute);
            else
            {
                _turnSignal(currentRoute, SIGNAL_PERMIT, DefaultSignalPeriod);
                return;
            }

            long interval;
            if (aRoute == ROUT_PRIMARY)
                interval = _calculateInterval(primaryCrispRating, secondaryCrispRating);
            else
                interval = _calculateInterval(secondaryCrispRating, primaryCrispRating);

            if (aRoute == currentRoute)
                _turnSignal(aRoute, SIGNAL_PERMIT, interval);
            else
                _turnSignal(aRoute, SIGNAL_WARNING, WarningTime);
        }
    }
}
