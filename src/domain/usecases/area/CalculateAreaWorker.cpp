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
    //double TAccessibility = 0;
    //int kolvo = 0;
    //double STime = 0;
    int index = 0;
    for(int k=0; k < graph.airports.size(); k++) {
        atime.append(ATime(graph.airports.at(k).id,0.0, 0));
    }
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
                //kolvo ++;
                auto d = distanceInKm(currentLon, currentLat, minDistanceAirport.lon, minDistanceAirport.lat);
//                        sqrt(
//                        pow(currentLat - minDistanceAirport.lat, 2) + pow(currentLon - minDistanceAirport.lon, 2));
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
                //STime = STime +(d/60);
                for (int l=0; l < atime.size(); l++) {
                    if (airportId == atime.at(l).id) {
                        atime[l].aTime = + d/60;
                        atime[l].count ++;
                    }
                }
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
    for (int i=0; i < atime.size(); i++) {
        auto tacces = atime[i].aTime / atime[i].count;
        tAcc.append(TAccessibility(atime.at(i).id, tacces));
    }
    //TAccessibility = STime / kolvo;
    //qDebug() << graph.airports.size();
    //qDebug() << "Количество расчетов расстояния" << kolvo;
    //qDebug() << "Суммарное время до аэропортов" << STime;
    //qDebug() << "Общая транспортная доступность всех аэропортов = " << TAccessibility;
    qDebug() << "CalculateAreaWorker все посчитал" << points.size();

    auto area = Area(points);
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
