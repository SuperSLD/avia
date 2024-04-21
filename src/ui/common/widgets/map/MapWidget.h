//
// Created by Леонид Соляной on 16.04.2024.
//

#ifndef AVIA_MAPWIDGET_H
#define AVIA_MAPWIDGET_H


#include <QFrame>
#include <QJsonDocument>
#include "src/data/db/dbconnector/models/routemodel/RouteModel.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"

class MapWidget: public QFrame {

private:
    int AIRPORT_POINT_SIZE_MAX = 15;
    int AIRPORT_POINT_SIZE_MIN = 8;
    int maxAirportFlightCount = 0;
    QList<QString> colors = QList<QString> {
            "#86C28E",
            "#BBE48D",
            "#E0E182",
            "#F6C961",
            "#F1AE52",
            "#FDA149",
            "#F87D1E",
    };

    QList<RouteModel*> routes;
    QList<AirportModel> airports;

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
    void setAirports(QList<AirportModel> airports);

private slots:
    void onZoomChange(QString name);
};


#endif //AVIA_MAPWIDGET_H
