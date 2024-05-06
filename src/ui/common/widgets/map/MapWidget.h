//
// Created by Леонид Соляной on 16.04.2024.
//

#ifndef AVIA_MAPWIDGET_H
#define AVIA_MAPWIDGET_H


#include <QFrame>
#include <QJsonDocument>
#include <QHBoxLayout>
#include "src/data/db/dbconnector/models/routemodel/RouteModel.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/domain/models/area/Area.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/domain/usecases/area/countryshape/CountryShape.h"

class MapWidget: public QFrame {

private:

    CountryShape *country;
    QFrame *areaCard;
    QHBoxLayout *areaCardContainer;

    int AIRPORT_POINT_SIZE_MAX = 15;
    int AIRPORT_POINT_SIZE_MIN = 8;
    QList<QString> colors = QList<QString> {
            "#88C78C",
            "#9DC878",
            "#AFC866",
            "#C2C952",
            "#D7CA3E",
            "#E9CB2C",
            "#FCCC19",
            "#FFC216",
            "#FFB716",
            "#FFAB16",
            "#FF9316",
            "#FF8816",
            "#FF8816",
            "#FF7E16",
    };

    QList<RouteModel*> routes;
    TransportGraphModel graph;
    bool airportsVisible = true;
    Area area;
    bool areaVisible = true;
    bool baseGraphVisible = true;

    QPoint latLonToXY(double lat, double lon);

    int lastCameraX = 0;
    int lastCameraY = 0;
    int clickX = -1;
    int clickY = -1;
    int cameraX = 0;
    int cameraY = 0;
    bool isMove = false;
    double zoom = 1;

    void drawBack(QPainter *painter);
    void drawArea(QPainter *painter);
    void drawAirports(QPainter *painter);
    void drawGraph(TransportGraphModel graphForDraw, QPainter *painter, QString color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    MapWidget();
    ~MapWidget();

    void clearList(QLayout *list);

    void setRoutes(QList<RouteModel*> routes);
    void setAirports(TransportGraphModel graph);
    void setArea(Area area);

private slots:
    void onZoomChange(QString name);
    void onChangeAirportsVisible(bool checked);
    void onChangeAreaVisible(bool checked);
    void onChangeBaseGraphVisible(bool checked);
};


#endif //AVIA_MAPWIDGET_H
