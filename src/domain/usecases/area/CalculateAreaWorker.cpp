//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateAreaWorker.h"
#include "src/domain/usecases/area/countryshape/CountryShape.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"

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
            if (country.pointInCountry(currentLon, currentLat)) {
                auto minDistanceAirport = graph.getMinDistanceAirport(currentLon, currentLat);
                airportId = minDistanceAirport.id;
                auto d = sqrt(
                        pow(currentLat - minDistanceAirport.lat, 2) + pow(currentLon - minDistanceAirport.lon, 2));
//            emit direction(
//                currentLon,
//                currentLat,
//                minDistanceAirport.lon,
//                minDistanceAirport.lat
//            );
//            while (!requestFinished) {}
//            lonPoints.append(currentRequestPoint);
//            sleep(5);
                //qDebug() << "loaded point data:" << (currentRequestPoint.isValid ? "T" : "F") << currentRequestPoint.duration;
                lonPoints.append(
                        AreaPoint(
                                airportId,
                                d,
                                0,
                                lonDif / lonIterations,
                                latDif / latIterations,
                                currentLon,
                                currentLat
                        )
                );
            }
            emit onChangeProgress((index * 100) / (latIterations * lonIterations));
        }
        points.append(lonPoints);
    }

    qDebug() << "CalculateAreaWorker все посчитал" << points.size();

    emit resultReady(Area(points));
}

void CalculateAreaWorker::directionLoad(OSMDirectionModel direction) {
    requestFinished = true;
    if (direction.isValid) {
        currentRequestPoint = AreaPoint(
                    airportId,
                    direction.distance,
                    direction.duration,
                    lonDif,
                    latDif,
                    currentLon,
                    currentLat
                );
    } else {
        currentRequestPoint = AreaPoint(airportId);
    }
}
