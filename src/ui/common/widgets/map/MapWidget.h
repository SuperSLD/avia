//
// Created by Леонид Соляной on 16.04.2024.
//

#ifndef AVIA_MAPWIDGET_H
#define AVIA_MAPWIDGET_H


#include <QFrame>
#include <QJsonDocument>
#include "src/data/db/dbconnector/models/routemodel/RouteModel.h"

class MapWidget: public QFrame {

private:
    QList<RouteModel*> routes;
    QPoint latLonToXY(double lat, double lon);
    QJsonDocument russia;

    int lastCameraX = 0;
    int lastCameraY = 0;
    int clickX = -1;
    int clickY = -1;
    int cameraX = 0;
    int cameraY = 0;
    bool isMove = false;
    double zoom = 1;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    MapWidget();
    ~MapWidget();

    void setRoutes(QList<RouteModel*> routes);

private slots:
    void onZoomChange(QString name);
};


#endif //AVIA_MAPWIDGET_H
