//
// Created by Леонид Соляной on 21.04.2024.
//

#include <QJsonArray>
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

AirportModel::AirportModel(QJsonObject json) {
    this->id = json["id"].toString();
    this->name = json["name"].toString();
    this->city = json["city"].toString();
    this->lon = json["lon"].toDouble();
    this->lat = json["lat"].toDouble();
    this->passengersCountOut = json["passengersCountOut"].toInt();
    this->passengersCountIn = json["passengersCountIn"].toInt();
    foreach(auto val, json["connectedAirports"].toArray()) {
        connectedAirports.append(val.toString());
    }
    this->flightCount = json["flightCount"].toInt();
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

QJsonObject AirportModel::toJson() {
    auto json = QJsonObject();
    json["id"] = id;
    json["name"] = name;
    json["city"] = city;
    json["lon"] = lon;
    json["lat"] = lat;
    json["passengersCountOut"] = (int) passengersCountOut;
    json["passengersCountIn"] = (int) passengersCountIn;
    auto airports = QJsonArray();
    foreach(auto airport, connectedAirports) {
        airports.append(airport);
    }
    json["connectedAirports"] = airports;
    json["flightCount"] = flightCount;
    return json;
}