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

    QList<RouteModel*> routes;
    TransportGraphModel graph;
    QString save = "s0";
    QHash<QString, TransportGraphModel> saves;

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
    void setGraph(TransportGraphModel graph, QString key = "");
    void setArea(Area area);

private slots:
    void onZoomChange(QString name);
    void onChangeAirportsVisible(bool checked);
    void onChangeAreaVisible(bool checked);
    void onChangeBaseGraphVisible(bool checked);

    void onSaveSelected(QString save);
};


#endif //AVIA_MAPWIDGET_H
