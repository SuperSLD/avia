//
// Created by Леонид Соляной on 22.04.2024.
//

#include <QJsonArray>
#include <QHash>
#include "TransportGraphModel.h"

#include "src/domain/usecases/math/geometry.h"
#include "src/domain/models/analytics/view/TitleAnalyticsCell.h"
#include "src/domain/models/analytics/view/chart/ChartAnalyticsCell.h"

using namespace geometry;

TransportGraphModel::TransportGraphModel(QList<AirportModel> airports, QString save, double greed, double gregariousness) {
    this->airports = airports;
    foreach(auto airport, airports) {
        if (maxAirportFlightCount < airport.flightCount) {
            maxAirportFlightCount = airport.flightCount;
        }
    }
    this->greed = greed;
    this->gregariousness = gregariousness;
    this->save = save;
    calcDataForView();
    calcAnalyticData();
}

TransportGraphModel::TransportGraphModel(QJsonObject json) {
    foreach(auto airport, json["airports"].toArray()) {
        airports.append(AirportModel(airport.toObject()));
    }
    foreach(auto airport, airports) {
        if (maxAirportFlightCount < airport.flightCount) {
            maxAirportFlightCount = airport.flightCount;
        }
    }
    this->greed = json["greed"].toDouble();
    this->gregariousness = json["gregariousness"].toDouble();
    this->save = json["save"].toString();
    calcDataForView();
    calcAnalyticData();
}

TransportGraphModel TransportGraphModel::getWithEmptyEdges() {
    QList<AirportModel> emptyEdgesList;
    foreach(auto airport, airports) {
        emptyEdgesList.append(airport.getWithEmptyEdges());
    }
    return {emptyEdgesList};
}

AirportModel TransportGraphModel::getMinDistanceAirport(double lon, double lat) {
    double minDistance = 100000000000.0;
    AirportModel minDistanceAirport;
    foreach(auto airport, airports) {
        auto distance = distanceInKm(lon, lat, airport.lon, airport.lat);
        if (distance < minDistance) {
            minDistance = distance;
            minDistanceAirport = airport;
        }
    }
    return minDistanceAirport;
}

QJsonObject TransportGraphModel::toJson() {
    auto json = QJsonObject();
    auto airportsJson = QJsonArray();
    foreach(auto airport, airports) {
        airportsJson.append(airport.toJson());
    }
    json["airports"] = airportsJson;
    json["greed"] = greed;
    json["gregariousness"] = gregariousness;
    json["save"] = save;
    return json;
}

void TransportGraphModel::calcDataForView() {
    QHash<QString, QList<double>> lines;
    foreach(auto airport, airports) {
        foreach(auto connectedAirportId, airport.connectedAirports) {
            auto lineId = airport.id + connectedAirportId;
            auto revLineId = connectedAirportId + airport.id;
            if (!lines.contains(lineId) && !lines.contains(revLineId)) {
                auto connectedAirport = findAirport(connectedAirportId);
                lines[lineId] = QList<double> {
                    airport.lon,
                    airport.lat,
                    connectedAirport.lon,
                    connectedAirport.lat,
                };
            }
        }
    }
    viewLines = lines.values();
}

AirportModel TransportGraphModel::findAirport(QString id) {
    AirportModel airport;
    foreach(auto a, airports) {
        if (a.id == id) airport = a;
    }
    return airport;
}

void TransportGraphModel::calcAnalyticData() {
    auto allIn = 0.0;
    auto allOut = 0.0;
    foreach(auto a, airports) {
        passCount += a.passengersCountOut + a.passengersCountIn;
        allIn += a.passengersCountIn;
        allOut += a.passengersCountOut;
    }
    passCountPieChart.append(
        ChartLine(
                QList<QString>({colorPrimary(), colorSecondary()}),
                QList<double>({(double) allOut, (double)  allIn}),
                QList<QString>({"В аэропорты", "Из аэропортов"})
        )
    );
}

QList<AnalyticsRow> TransportGraphModel::getRows() {
    QList<AnalyticsRow> rows;
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
               new TitleAnalyticsCell("Результаты вычислений графа " + save),
        }), true)
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
               new NumberAnalyticsCell(QString::number(airports.count()), "Количество аэропортов", colorSecondary()),
               new NumberAnalyticsCell(QString::number(viewLines.size()), "Количество связей", colorPrimary()),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
           new NumberAnalyticsCell(QString::number(greed), "Жадность", colorPrimary()),
           new NumberAnalyticsCell(QString::number(gregariousness), "Стадность", colorPrimary()),
       }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
           new ChartAnalyticsCell("pie", "Баланс пассажиров", passCountPieChart),
           new NumberAnalyticsCell(QString::number(passCount) + "\nпассажиров", "Общее количество\nперевезенных пассажиров", colorSecondary()),
        }))
    );
    return rows;
}