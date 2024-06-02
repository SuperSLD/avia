//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateAreaWorker.h"
#include "src/domain/usecases/area/countryshape/CountryShape.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"
#include <unistd.h>

void CalculateAreaWorker::run() {
    auto country = CountryShape("russia");
    lonDif = country.maxLon - country.minLon;
    auto lonIterations = (int) lonDif / DISTANCE_BETWEEN_POINT;
    latDif = country.maxLat - country.minLat;
    auto latIterations = (int) latDif / DISTANCE_BETWEEN_POINT;
    qDebug() << "CountryShape" << lonDif << lonIterations << latDif << latIterations;
    QList<QList<AreaPoint>> points;
    int index = 0;
    for (int i = 0; i < latIterations; i++) {
        QList<AreaPoint> lonPoints;
        for (int j = 0; j < lonIterations; j++) {
            index++;
            requestFinished = false;
            currentLon = country.minLon + j * lonDif / (double) lonIterations;
            currentLat = country.minLat + i * latDif / (double) latIterations;
            auto p = country.pointInCountry(currentLon, currentLat);
            if (p >= 0) {
                auto minDistanceAirport = graph.getMinDistanceAirport(currentLon, currentLat);
                airportId = minDistanceAirport.id;
                auto d = distanceInKm(currentLon, currentLat, minDistanceAirport.lon, minDistanceAirport.lat);
                lonPoints.append(
                        AreaPoint(
                                airportId,
                                d,
                                d / 60.0,
                                lonDif / lonIterations,
                                latDif / latIterations,
                                currentLon,
                                currentLat,
                                p
                        )
                );
            }
            emit onChangeProgress((index * 100) / (latIterations * lonIterations));
        }
        points.append(lonPoints);
    }

    auto area = Area(points);
    area.setTAccessibility(area.calcTime(graph));
    settingsRepository->setJson("area", area.toJson());
    emit resultReady(area);
}

void CalculateAreaWorker::directionLoad(OSMDirectionModel direction) {
    auto country = CountryShape("russia");
    requestFinished = true;
    auto p = country.pointInCountry(currentLon, currentLat);;
    if (direction.isValid) {
        currentRequestPoint = AreaPoint(
                    airportId,
                    direction.distance,
                    direction.duration,
                    lonDif,
                    latDif,
                    currentLon,
                    currentLat,
                    p
                );
    } else {
        currentRequestPoint = AreaPoint(airportId);
    }
}
