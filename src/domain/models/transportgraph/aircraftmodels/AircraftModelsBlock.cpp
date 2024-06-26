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
    file.close();
    auto useCount = 0;
    foreach(auto v, array) {
        auto aircraft = v.toObject();
        auto aircraftModel = Aircraft(
                aircraft["model"].toString(),
                aircraft["modelName"].toString(),
                aircraft["seatsCount"].toInt(),
                aircraft["kilometerCost"].toDouble(),
                aircraft["speed"].toDouble(),
                aircraft["range"].toDouble(),
                aircraft["use"].toBool(),
                aircraft["vpp"].toDouble()
        );
        aircraftList.append(aircraftModel);
        if (aircraftList.last().use) {
            useCount++;
            middleCount += aircraftList.last().seatsCount;
        }
    }
    qDebug() << "Количество загруженных моделей самолетов" << aircraftList.size();
    middleCount /= useCount;

    file.setFileName(":/resc/resc/jsondata/russia_vpp.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    array = QJsonDocument::fromJson(val).array();
    foreach(auto v, array) {
        auto airport = v.toObject();
        vppInfo[airport["name"].toString()] = airport["len"].toDouble();
    }
}

int AircraftModelsBlock::passengersCount(double k, QString aircraftModel) {
    foreach(auto aircraft, aircraftList) {
        if (aircraft.model == aircraftModel) return k * aircraft.seatsCount;
    }
    return middleCount;
}

Aircraft AircraftModelsBlock::getOptimalAircraft(double distance, QString airportId, int outPassCount) {
    auto min = 299792458000.0;
    Aircraft optimal = aircraftList.first();
    if (maxCost == -1) {
        foreach(auto aircraft, aircraftList) {
                auto C = aircraft.kilometerCost * distance;
                auto p1 = (aircraft.range / distance);
                auto p2 = outPassCount / (double) aircraft.seatsCount;
                auto p3 = (24*30) / (distance / aircraft.speed);
                if (C > maxCost) maxCost = C;
                if (p1 > maxP1) maxP1 = p1;
                if (p2 > maxP2) maxP2 = p2;
                if (p3 > maxP3) maxP3 = p3;
        }
    }
    foreach(auto aircraft, aircraftList) {
        if (aircraft.use && aircraft.range >= distance && aircraft.vppLen <= vppInfo[airportId]) {
            /// стоимость выполнения рейса
            auto C = aircraft.kilometerCost * distance;
            /// штраф за превышение нужной дальности полета
            auto p1 = (aircraft.range / distance);
            /// сколько самолетов нужно
            auto p2 = outPassCount / (double) aircraft.seatsCount;
            /// награда за скорость полета самолета
            auto p3 = (24*30) / (distance / aircraft.speed);
            auto current = pow(C/maxCost, 0.1) * pow(p1/maxP1, 0.1) * pow(p2/maxP2, 0.4) * pow(p3/maxP3, 0.4);
            if (current < min) {
                optimal = aircraft;
                min = current;
            }
        }
    }
    return optimal;
}

Aircraft AircraftModelsBlock::getByModel(QString model) {
    foreach(auto aircraft, aircraftList) {
        if (aircraft.model == model) return aircraft;
    }
    return aircraftList.first();
}

int AircraftModelsBlock::getAircraftCount() {
    return aircraftList.size();
}

QList<QString> AircraftModelsBlock::getKeys() {
    auto keys = QList<QString>();
    foreach(auto a, aircraftList) {
        keys.append(a.model);
    }
    return keys;
}
