//
// Created by Леонид Соляной on 21.04.2024.
//

#include "AirportModel.h"

AirportModel::AirportModel(
        QString id,
        QString name,
        QString city,
        double lon,
        double lat,
        QList<QString> connectedAirports
) {
    this->id = id;
    this->name = name;
    this->city = city;
    this->lon = lon;
    this->lat = lat;
    this->connectedAirports = connectedAirports;
}

QString AirportModel::getId() {
    return id;
}

void AirportModel::addConnection(QString id) {
    if (!connectedAirports.contains(id)) {
        connectedAirports.append(id);
    }
}

void AirportModel::incFlight() {
    flightCount++;
}

AirportModel AirportModel::getWithEmptyEdges() {
    return AirportModel(
        id,
        name,
        city,
        lon,
        lat,
        QList<QString>()
    );
}
