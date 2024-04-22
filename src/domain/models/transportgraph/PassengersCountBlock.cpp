//
// Created by Леонид Соляной on 22.04.2024.
//

#include "PassengersCountBlock.h"
#include <QIODevice>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

PassengersCountBlock::PassengersCountBlock() {
    QFile file;
    file.setFileName(":/resc/resc/jsondata/aircraft_models.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto val = file.readAll();
    auto array = QJsonDocument::fromJson(val).array();
    foreach(auto v, array) {
        auto aircraft = v.toObject();
        seatsByType[aircraft["model"].toString()] = aircraft["seatsCount"].toInt();
        middleCount += aircraft["seatsCount"].toInt();
    }
    middleCount /= array.count();
}

int PassengersCountBlock::passengersCount(double k, QString aircraftModel) {
    if (seatsByType.contains(aircraftModel)) {
        return k * seatsByType[aircraftModel];
    } else {
        return middleCount;
    }
}
