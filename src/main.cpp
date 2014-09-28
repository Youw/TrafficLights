#include "uiwindow.h"
#include "crossroad.h"
#include "loader.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CrossRoad crossroad(
        Loader::getLeftRoad(),
        Loader::getTopRoad(),
        Loader::getRightRoad(),
        Loader::getBottomRoad());
  UIWindow mainWindow;
  QTimer timer;

  crossroad.setCrossRoadPainter(mainWindow.getCrossRoadPainter());

  QObject::connect(&timer,SIGNAL(timeout()),&crossroad,SLOT(timerTick()));
  QObject::connect(&timer,SIGNAL(timeout()),&mainWindow,SLOT(paintRoads()));

  timer.start(500);

  mainWindow.show();
  return a.exec();
}
