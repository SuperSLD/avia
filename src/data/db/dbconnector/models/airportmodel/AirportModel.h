//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_AIRPORTMODEL_H
#define AVIA_AIRPORTMODEL_H


#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class AirportModel: public BaseDBModel{

public:

    QString id;
    QString name;
    QString city;
    double lon;
    double lat;
    QList<QString> connectedAirports;
    int flightCount = 1;

    AirportModel(
        QString id,
        QString name,
        QString city,
        double lon,
        double lat,
        QList<QString> connectedAirports
    );
    AirportModel() {};

    QString getId() override;

    void addConnection(QString id);
    void incFlight();
};


#endif //AVIA_AIRPORTMODEL_H
