#ifndef UIWINDOW_H
#define UIWINDOW_H

#include <QMainWindow>
#include <QLabel>

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


private slots:
  void on_freque_primary_sliderMoved(int position);

  void on_freque_secondary_sliderMoved(int position);

  void on_dispersion_primary_sliderMoved(int position);

  void on_disparsion_secondary_sliderMoved(int position);

private:
  Ui::UIWindow *ui;

  QLabel* freque_primary = new QLabel();
  QLabel* freque_secondary = new QLabel();

  QLabel* dispersion_primary = new QLabel();
  QLabel* dispersion_secondary = new QLabel();
};

#endif // UIWINDOW_H
