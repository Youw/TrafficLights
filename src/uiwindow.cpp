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
    freque_primary->setText(QString::number(GlobalSettings::time_to_next_car_primary));
    freque_secondary->setText(QString::number(GlobalSettings::time_to_next_car_secondary));
    dispersion_primary->setText(QString::number(GlobalSettings::dispersion_time_next_car_primary));
    dispersion_secondary->setText(QString::number(GlobalSettings::dispersion_time_next_car_secondary));

    ui->statusBar->addWidget(new QLabel("Primary period:"));
    ui->statusBar->addWidget(freque_primary);
    ui->statusBar->addWidget(new QLabel("Primary dispersion:"));
    ui->statusBar->addWidget(dispersion_primary);

    ui->statusBar->addWidget(new QLabel("Secondary period:"));
    ui->statusBar->addWidget(freque_secondary);
    ui->statusBar->addWidget(new QLabel("Secondary dispersion:"));
    ui->statusBar->addWidget(dispersion_secondary);
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
  freque_primary->setText(QString::number(position));
}

void UIWindow::on_freque_secondary_sliderMoved(int position)
{
  GlobalSettings::time_to_next_car_secondary = position;
  freque_secondary->setText(QString::number(position));
}

void UIWindow::on_dispersion_primary_sliderMoved(int position)
{
  GlobalSettings::dispersion_time_next_car_primary = position;
  dispersion_primary->setText(QString::number(position));
}

void UIWindow::on_disparsion_secondary_sliderMoved(int position)
{
  GlobalSettings::dispersion_time_next_car_secondary = position;
  dispersion_secondary->setText(QString::number(position));
}
