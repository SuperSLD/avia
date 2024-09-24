//
// Created by Егор Рыжов on 06.06.2024.
//

#ifndef CALCNEWAREA_H
#define CALCNEWAREA_H

#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/data/net/osmnetrepository/OSMNetRepository.h"
#include "src/domain/models/area/Area.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/domain/usecases/area/countryshape/CountryShape.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"
#include <unistd.h>

class CalcNewArea: public BaseModel {

public:
    TransportGraphModel graph;
    double DISTANCE_BETWEEN_POINT = 0.5;
    double lonDif;
    double latDif;
    double currentLon;
    double currentLat;
    bool requestFinished = false;
    QString airportId;

    CalcNewArea (){}

    QList<QList<AreaPoint>> calcPoints (TransportGraphModel graph)
    {
        this->graph=graph;
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
                    if (!(currentLat >= 70.67))
                    {
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
                    else
                    {
                        auto minDistanceAirport = graph.getMinDistanceAirport(currentLon, currentLat);
                        airportId = minDistanceAirport.id;
                        auto d = distanceInKm(currentLon, currentLat, minDistanceAirport.lon, minDistanceAirport.lat);
                        if (minDistanceAirport.lon > 70.67)
                        {
                            lonPoints.append(
                                AreaPoint(
                                        airportId,
                                        d,
                                        d / 35.0,
                                        lonDif / lonIterations,
                                        latDif / latIterations,
                                        currentLon,
                                        currentLat,
                                        p
                                )
                            );
                        }
                        else
                        {
                            double h1 = currentLon - 70.67;
                            double h2 = 70.67 - minDistanceAirport.lon;
                            double h = currentLon - minDistanceAirport.lon;
                            double k1 = h1/h ;
                            double k2 = h2/h ;
                            double durT = d*k1/35 + d*k2/60;
                            lonPoints.append(
                                AreaPoint(
                                        airportId,
                                        d,
                                        durT,
                                        lonDif / lonIterations,
                                        latDif / latIterations,
                                        currentLon,
                                        currentLat,
                                        p
                                )
                            );
                        }
                    }
                }
            }
            points.append(lonPoints);
        }
        return points;
    }
};

#endif //CALCNEWAREA_H
