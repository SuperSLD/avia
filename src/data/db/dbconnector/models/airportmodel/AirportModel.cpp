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
        long passengersCountOut,
        long passengersCountIn,
        QList<QString> connectedAirports
) {
    this->id = id;
    this->name = name;
    this->city = city;
    this->lon = lon;
    this->lat = lat;
    this->passengersCountOut = passengersCountOut;
    this->passengersCountIn = passengersCountIn;
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
        passengersCountOut,
        passengersCountIn,
        QList<QString>()
    );
}

void AirportModel::incPassengerCount(int count, bool in) {
    if (in) {
        passengersCountIn += count;
    } else {
        passengersCountOut += count;
    }
}
