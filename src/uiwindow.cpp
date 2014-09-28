#include "uiwindow.h"
#include "ui_uiwindow.h"

#include <QPainter>

UIWindow::UIWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIWindow)
{
    ui->setupUi(this);
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
