#ifndef UIWINDOW_H
#define UIWINDOW_H

#include <QMainWindow>

#include "road.h"
#include "crossroadpainter.h"

namespace Ui {
class UIWindow;
}

class UIWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit UIWindow(QWidget *parent = 0);
  ~UIWindow();

  CrossRoadPainter& getCrossRoadPainter() const;

public slots:
  void paintRoads();


private:
  Ui::UIWindow *ui;
};

#endif // UIWINDOW_H
