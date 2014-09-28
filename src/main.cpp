#include "uiwindow.h"
#include <QApplication>

#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UIWindow w;
    w.show();

    QTimer timer;

    QObject::connect(&timer,SIGNAL(timeout()),&w,SLOT(paintRoads()));

    timer.start(500);

    return a.exec();
}
