//
// Created by Леонид Соляной on 22.04.2024.
//

#include "AircraftModelsBlock.h"
#include <QIODevice>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

AircraftModelsBlock::AircraftModelsBlock() {
    QFile file;
    file.setFileName(":/resc/resc/jsondata/aircraft_models.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto val = file.readAll();
    auto array = QJsonDocument::fromJson(val).array();
    foreach(auto v, array) {
        auto aircraft = v.toObject();
        aircraftList.append(
            Aircraft(
                aircraft["model"].toString(),
                aircraft["modelName"].toString(),
                aircraft["seatsCount"].toInt(),
                aircraft["kilometerCost"].toDouble(),
                aircraft["speed"].toDouble(),
                aircraft["range"].toDouble(),
                aircraft["use"].toBool()
            )
        );
        middleCount += aircraft["seatsCount"].toInt();
    }
    middleCount /= array.count();
}

int AircraftModelsBlock::passengersCount(double k, QString aircraftModel) {
    foreach(auto aircraft, aircraftList) {
        if (aircraft.model == aircraftModel) return k * aircraft.seatsCount;
    }
    return middleCount;
}

Aircraft AircraftModelsBlock::getOptimalAircraft(double distance, double passCount) {
    return aircraftList.first();
}
