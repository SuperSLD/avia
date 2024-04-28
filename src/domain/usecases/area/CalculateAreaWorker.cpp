//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateAreaWorker.h"
#include "src/domain/usecases/area/countryshape/CountryShape.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"

void CalculateAreaWorker::run() {

    auto country = CountryShape("russia");

    auto lonDif = country.maxLon - country.minLon;
    auto lonIterations = (int) lonDif / DISTANCE_BETWEEN_POINT;
    auto latDif = country.maxLat - country.minLat;
    auto latIterations = (int) latDif / DISTANCE_BETWEEN_POINT;
    qDebug() << "CountryShape" << lonDif << lonIterations << latDif << latIterations;
    QList<QList<AreaPoint>> points;
    for (int i = 0; i < latIterations; i++) {
        for (int j = 0; j < lonIterations; j++) {
            requestFinished = false;
            netRep->direction(
                country.minLon + j * lonDif,
                country.minLat + i * latDif,
                55.4088, 37.9063
            );
            while (!requestFinished) {}

        }
    }

    qDebug() << "CalculateAreaWorker все посчитал";

    emit resultReady();
}

void CalculateAreaWorker::directionLoad(OSMDirectionModel direction) {
    requestFinished = true;
}
