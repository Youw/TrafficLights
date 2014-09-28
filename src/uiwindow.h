#ifndef UIWINDOW_H
#define UIWINDOW_H

#include"roadarea.h"

#include <QMainWindow>

namespace Ui {
class UIWindow;
}

class UIWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIWindow(QWidget *parent = 0);
    ~UIWindow();

signals:
    void setLeftRoad(const Road* road);
    void setRightRoad(const Road* road);
    void setTopRoad(const Road* road);
    void setBottomRoad(const Road* road);

public slots:
    void paintRoads();


private:
    Ui::UIWindow *ui;
};

#endif // UIWINDOW_H
