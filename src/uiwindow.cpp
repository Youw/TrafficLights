#include "uiwindow.h"
#include "ui_uiwindow.h"

#include <QPainter>
#include "globalsettings.h"

UIWindow::UIWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIWindow)
{
    ui->setupUi(this);
    ui->freque_primary->setValue(GlobalSettings::time_to_next_car_primary);
    ui->freque_secondary->setValue(GlobalSettings::time_to_next_car_secondary);
    ui->dispersion_primary->setValue(GlobalSettings::dispersion_time_next_car_primary);
    ui->disparsion_secondary->setValue(GlobalSettings::dispersion_time_next_car_secondary);
}

UIWindow::~UIWindow()
{
    delete ui;
}

void UIWindow::paintRoads() {
    ui->crossroad->update();
}

CrossRoadPainter& UIWindow::getCrossRoadPainter() const {
  return *ui->crossroad;
}

void UIWindow::on_freque_primary_sliderMoved(int position)
{
  GlobalSettings::time_to_next_car_primary = position;
}

void UIWindow::on_freque_secondary_sliderMoved(int position)
{
  GlobalSettings::time_to_next_car_secondary = position;
}

void UIWindow::on_dispersion_primary_sliderMoved(int position)
{
  GlobalSettings::dispersion_time_next_car_primary = position;
}

void UIWindow::on_disparsion_secondary_sliderMoved(int position)
{
  GlobalSettings::dispersion_time_next_car_secondary = position;
}
