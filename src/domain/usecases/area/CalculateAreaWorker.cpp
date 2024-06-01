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
    int kolvo = 0;
    TAcces =0;
    //double STime = 0;
    int index = 0;
    //for(int k=0; k < graph.airports.size(); k++) {
      //  atime.append(ATime(graph.airports.at(k).id,0.0, 0));
    //}
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
                //for (int l=0; l < atime.size(); l++) {
                    //if (airportId == atime.at(l).id) {
                        //atime[l].aTime = atime[l].aTime + (d/60);
                        //atime[l].count ++;
                    //}
                //}
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

                //lonPoints.at(1).humanCount;
            }
            emit onChangeProgress((index * 100) / (latIterations * lonIterations));
        }
        for (int l = 0; l < lonPoints.size(); l++)
        {
            if (lonPoints.at(l).lon >= 69.8 && lonPoints.at(l).lon <= 77.3 && lonPoints.at(l).lat >= 73.0 && lonPoints.at(l).lat <= 113.55)
            {
                lonPoints[l].isValid = false;
            }
        }
        points.append(lonPoints);
    }
    for (int i=0; i < points.size(); i++)
    {
        for (int j =0; j < points.at(i).size(); j++)
        {
            double dur1 = points.at(i).at(j).duration; // длительность поездки на автомобиле в зоне конечного аэропорта
            double averageTime = 0.0; // среднее время
            int countOf = 0; // количество маршрутов для рассматриваемой зоны
            double dur2 = 0.0; // длительность перелета из начального аэропорта в конечный
            double dur3 = 0.0; // длительность поездки на автомобиле в зоне начального аэропорта
            int indIn = 0; // индекс конечного аэропорта
            int indOut = 0; // индекс начального аэропорта
            for (int u=0; u < graph.airports.size(); u++)
            {
                if (graph.airports.at(u).id == points.at(i).at(j).airportId) indIn = u;
            }
            long PassInAirport = graph.airports.at(indIn).passengersCountIn; // общий пассажиропоток на конечном аэропорте
            long PassOutAirport =0; // общий пассажиропоток на начальном аэропорте
            for (int y=0; y < graph.airports.at(indIn).connectedAirports.size(); y++)
            {
                double distanceOfFly = 0.0; // дистанция перелета
                double PassFromTo = 0; // пассажиропотоке на конкретном перелете
                for (int b = 0; b < graph.airports.size(); b++)
                {
                    if (graph.airports.at(indIn).connectedAirports.at(y) == graph.airports.at(b).id)
                    {
                        indOut = b;
                        distanceOfFly = distanceInKm(graph.airports.at(indIn).lon, graph.airports.at(indIn).lat, graph.airports.at(indOut).lon, graph.airports.at(indOut).lat);
                        dur2 = distanceOfFly / 500;
                        PassOutAirport = graph.airports.at(indOut).passengersCountOut;
                        PassFromTo = graph.airports.at(indIn).connectedPassCount.value(graph.airports.at(indOut).id);
                        for (int f = 0; f < points.size(); f++)
                        {
                            for (int g = 0; g < points.at(f).size(); g++)
                            {
                                if (points.at(f).at(g).airportId == graph.airports.at(indOut).id)
                                {
                                    dur3 = points.at(f).at(g).duration;
                                    averageTime = averageTime +(dur1 * (PassFromTo/PassInAirport) + dur2 + dur3 * (PassFromTo/PassOutAirport));
                                    countOf ++;
                                }
                            }
                        }
                    }
                }
            }
            //qDebug() << averageTime << ", количество = " << countOf;
            averageTime = averageTime / countOf;
            tAcc.append(TAccessibility(points.at(i).at(j).lon, points.at(i).at(j).lat, averageTime));
        }
    }
    double summm= 0.0;
    int kolichestvo = 0;
    for (int tt =0; tt < tAcc.size(); tt++)
    {
        qDebug() << tAcc.at(tt).tAccessibility;
        summm = summm + tAcc[tt].tAccessibility;
        kolichestvo ++;
    }
    TAcces = summm / kolichestvo;
    //for (int i=0; i < atime.size(); i++) {
       // auto tacces = atime[i].aTime / atime[i].count;
        //tAcc.append(TAccessibility(atime.at(i).id, tacces));
    //}
    //for(int j=0; j < tAcc.size(); j++)
    //{
     //   if (tAcc.at(j).tAccessibility >0 )
       // {
         //   kolvo ++;
           // TAcces = TAcces + tAcc.at(j).tAccessibility;
       // }
    //}
    //qDebug() << tAcc.at(0).id << tAcc.at(0).tAccessibility ;
    //qDebug() << "TAcces" << TAcces;
    //TAcces = TAcces / kolvo;
    //TAccessibility = STime / kolvo;
    //qDebug() << graph.airports.size();
    //qDebug() << "Количество расчетов расстояния" << kolvo;
    //qDebug() << "Суммарное время до аэропортов" << STime;
    qDebug() << "Транспортная доступность России = " << TAcces;
    qDebug() << "CalculateAreaWorker все посчитал" << points.size();

    auto area = Area(points, TAcces);
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
