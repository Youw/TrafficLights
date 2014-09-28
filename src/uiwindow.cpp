#include "uiwindow.h"
#include "ui_uiwindow.h"

#include <QPainter>

UIWindow::UIWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(setTopRoad(const Road*)),ui->crossroad,SLOT(setTopRoad(const Road*)));
    connect(this,SIGNAL(setBottomRoad(const Road*)),ui->crossroad,SLOT(setBottomRoad(const Road*)));
    connect(this,SIGNAL(setLeftRoad(const Road*)),ui->crossroad,SLOT(setLeftRoad(const Road*)));
    connect(this,SIGNAL(setRightRoad(const Road*)),ui->crossroad,SLOT(setRightRoad(const Road*)));
}

UIWindow::~UIWindow()
{
    delete ui;
}

void UIWindow::paintRoads() {
    ui->crossroad->update();
}
