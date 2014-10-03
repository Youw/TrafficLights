#include "trafficlight.h"
#include "crossroad.h"
#include "globalsettings.h"
#include <QSettings>

#include <QDebug>

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
    interval *= MilisecondsPerSecond * GlobalSettings::time_scale;
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
void TrafficLight::GenerateIni(const QString & file_name) const
{
  QSettings settings(file_name, QSettings::IniFormat);

  settings.beginGroup("LinguistisVariables");
  settings.beginGroup("InputVariables");

  settings.beginGroup("ARouteRating");
  settings.setValue("name", "ARouteRating");
  settings.setValue("range_left", 0);
  settings.setValue("range_right", 100);
  settings.setValue("default_value", 10);
  settings.beginWriteArray("FuzzyValues");
  for (int i = 0; i < 6; i++)
  {
    settings.setArrayIndex(i);
    settings.setValue("Name", "name" + QString::number(i));
    settings.setValue("tr_left", (100 + 100 / 6.0) / 6.0 * i - 100 / 12.0);
    settings.setValue("tr_right", (100 + 100 / 6.0) / 6.0 * i + 100 / 12.0);
  }
  settings.endArray();
  settings.endGroup();

  settings.beginGroup("BRouteRating");
  settings.setValue("name", "BRouteRating");
  settings.setValue("range_left", 0);
  settings.setValue("range_right", 100);
  settings.setValue("default_value", 10);
  settings.beginWriteArray("FuzzyValues");
  for (int i = 0; i < 6; i++)
  {
    settings.setArrayIndex(i);
    settings.setValue("Name", "name" + QString::number(i));
    settings.setValue("tr_left", (100 + 100 / 6.0) / 6.0 * i - 100 / 12.0);
    settings.setValue("tr_right", (100 + 100 / 6.0) / 6.0 * i + 100 / 12.0);
  }
  settings.endArray();
  settings.endGroup();

  settings.endGroup();


  settings.beginGroup("OutputVariables");
  settings.beginGroup("NextSignal");
  settings.setValue("name", "NextSignal");
  settings.setValue("range_left", 0);
  settings.setValue("range_right", 100);
  settings.setValue("default_value", 10);
  settings.beginWriteArray("FuzzyValues");
  for (int i = 0; i < 6; i++)
  {
    settings.setArrayIndex(i);
    settings.setValue("Name", "name" + QString::number(i));
    settings.setValue("tr_left", (100 + 100 / 6.0) / 6.0 * i - 100 / 12.0);
    settings.setValue("tr_right", (100 + 100 / 6.0) / 6.0 * i + 100 / 12.0);
  }
  settings.endArray();
  settings.endGroup();
  settings.endGroup();

  settings.beginGroup("FuzzyRules");
  settings.beginWriteArray("Rules");
  for (int i = 0; i < 30; i++)
  {
    settings.setArrayIndex(i);
    settings.setValue("Rule" + QString::number(i), "some rule");
  }
  settings.endArray();
  settings.endGroup();

}
bool TrafficLight::SetConfig(const QString &file_name)
{
    QSettings settings(file_name,QSettings::IniFormat);

    engine = new fl::Engine("Traffic Light");

    QString str;
    double a, b, c;

    int n;
    settings.beginGroup("LinguistisVariables");
      settings.beginGroup("InputVariables");
        settings.beginGroup("ARouteRating");
          aRouteRating = new fl::InputVariable;
          aRouteRating->setEnabled(true);
          aRouteRating->setName(settings.value("name", "ARouteRating").toString().toStdString());
          aRouteRating->setRange(settings.value("range_left", 0).toDouble(), settings.value("range_right", 100).toDouble());
          n = settings.beginReadArray("FuzzyValues");
          for (int i = 0; i < n; i++)
          {
            settings.setArrayIndex(i);
            str = settings.value("Name","Def" + QString::number(i)).toString();
            a = settings.value("tr_left",(100 + 100 / 6.0) / 6.0 * i - 100 / 12.0).toDouble();
            b = settings.value("tr_middle",(100 + 100 / 6.0) / 6.0 * i - 100 / 12.0).toDouble();
            c = settings.value("tr_right",(100 + 100 / 6.0) / 6.0 * i + 100 / 12.0).toDouble();
            aRouteRating->addTerm(new fl::Triangle(str.toStdString(), a, b, c));
          }
          settings.endArray();
          engine->addInputVariable(aRouteRating);
        settings.endGroup();

        settings.beginGroup("BRouteRating");
          bRouteRating = new fl::InputVariable;
          bRouteRating->setEnabled(true);
          bRouteRating->setName(settings.value("name", "BRouteRating").toString().toStdString());
          bRouteRating->setRange(settings.value("range_left", 0).toDouble(), settings.value("range_right", 100).toDouble());
          n = settings.beginReadArray("FuzzyValues");
          for (int i = 0; i < n; i++)
          {
            settings.setArrayIndex(i);
            str = settings.value("Name","Def" + QString::number(i)).toString();
            a = settings.value("tr_left",(100 + 100 / 6.0) / 6.0 * i - 100 / 12.0).toDouble();
            b = settings.value("tr_middle",(100 + 100 / 6.0) / 6.0 * i - 100 / 12.0).toDouble();
            c = settings.value("tr_right",(100 + 100 / 6.0) / 6.0 * i + 100 / 12.0).toDouble();
            bRouteRating->addTerm(new fl::Triangle(str.toStdString(), a, b, c));
          }
          settings.endArray();
          engine->addInputVariable(bRouteRating);
        settings.endGroup();
      settings.endGroup();
      settings.beginGroup("OutputVariables");
        settings.beginGroup("NextSignal");
          nextSignalWhile = new fl::OutputVariable;
          nextSignalWhile->setEnabled(true);
          nextSignalWhile->setName(settings.value("name", "BRouteRating").toString().toStdString());
          nextSignalWhile->setRange(settings.value("range_left", 0).toDouble(), settings.value("range_right", 30).toDouble());
          n = settings.beginReadArray("FuzzyValues");
          for (int i = 0; i < n; i++)
          {
            settings.setArrayIndex(i);
            str = settings.value("Name","Def" + QString::number(i)).toString();
            a = settings.value("tr_left",(30 + 30 / 6.0) / 6.0 * i - 30 / 12.0).toDouble();
            b = settings.value("tr_middle",(30 + 30 / 6.0) / 6.0 * i - 30 / 12.0).toDouble();
            c = settings.value("tr_right",(30 + 30 / 6.0) / 6.0 * i + 30 / 12.0).toDouble();
            nextSignalWhile->addTerm(new fl::Triangle(str.toStdString(), a, b, c));
          }
          settings.endArray();
          engine->addOutputVariable(nextSignalWhile);
        settings.endGroup();
      settings.endGroup();
    settings.endGroup();

    settings.beginGroup("FuzzyRules");
    ruleBlock = new fl::RuleBlock;
    ruleBlock->setEnabled(true);
    ruleBlock->setName("");
    ruleBlock->setConjunction(new fl::Minimum);
    ruleBlock->setDisjunction(new fl::Maximum);
    ruleBlock->setActivation(new fl::Minimum);
    n = settings.beginReadArray("Rules");
    for (int i = 0; i < n; i++)
    {
      settings.setArrayIndex(i);
      str = settings.value("Rule" + QString::number(i), "dfbdrb e se   ef e af a a ae a    q sr g").toString();
      ruleBlock->addRule(fl::Rule::parse(str.toStdString(), engine));

    }
    settings.endArray();
    engine->addRuleBlock(ruleBlock);
    settings.endGroup();

    engine->configure("Minimum", "Maximum", "Minimum", "Maximum", "Centroid");

    std::string status;
    if (!engine->isReady(&status))
    {
      qDebug() << QString::fromStdString(status);
     // throw fl::Exception(status, FL_AT);
      return false;
    }

    connect(&timer, SIGNAL(timeout()), this, SLOT(ConsiderChange()));
    controllerType = FUZZY_CONTROL;//FUZZY in release
    return true;
}
bool TrafficLight::Start(ControllerType c_type)
{
    if (c_type == CRISP_CONTROL)
    {
        if (!(primaryPermitInterval > 0 && secondaryPermitInterval > 0))
          {
            ConsiderChange();
            return false;
          }
    }else
    {
        if (!engine)
            return false;
        _turnSignal(ROUT_PRIMARY, SIGNAL_PERMIT, 1);
    }
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
            nextInterval = WarningTime;
        else if (lastPrimaryRouteSignal == SIGNAL_PERMIT)
            nextInterval = secondaryPermitInterval;
        else
            nextInterval = primaryPermitInterval;
        _turnSignal(ROUT_PRIMARY, OppositSignal(lastPrimaryRouteSignal), nextInterval);
    }
    else
    {
        if (lastPrimaryRouteSignal != SIGNAL_WARNING)
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
              {
                _turnSignal(aRoute, SIGNAL_PERMIT, interval);
              }
            else
                _turnSignal(aRoute, SIGNAL_WARNING, WarningTime);
        }
    }
}
