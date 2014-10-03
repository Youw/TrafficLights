#include "uiwindow.h"
#include "crossroad.h"
#include "loader.h"
#include "globalsettings.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  UIWindow mainWindow;
  QTimer timer;


  Loader l;
  CrossRoad cross_road(
        l.getLeftRoad(),
        l.getTopRoad(),
        l.getRightRoad(),
        l.getBottomRoad());
  TrafficLight& traffic_light = l.getTrafficLight(&cross_road);
  traffic_light.Start(TrafficLight::CRISP_CONTROL);

  cross_road.setTrafficLight(&traffic_light);
  cross_road.setCrossRoadPainter(mainWindow.getCrossRoadPainter());

  QObject::connect(&timer,SIGNAL(timeout()),&cross_road,SLOT(timerTick()));
  QObject::connect(&timer,SIGNAL(timeout()),&mainWindow,SLOT(paintRoads()));

  timer.start(GlobalSettings::timer_interval);

  mainWindow.show();
  return a.exec();
}
