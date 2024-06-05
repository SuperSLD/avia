//
// Created by Леонид Соляной on 22.04.2024.
//

#include <QJsonArray>
#include <QHash>
#include <QThread>
#include "TransportGraphModel.h"

#include "src/domain/usecases/math/math_functions.h"
#include "src/domain/models/analytics/view/TitleAnalyticsCell.h"
#include "src/domain/models/analytics/view/chart/ChartAnalyticsCell.h"
#include "src/domain/models/analytics/view/EmpyAnalyticsCell.h"

#include "src/domain/models/transportgraph/PriorityQueue.h"
#include "src/domain/models/transportgraph/aircraftmodels/AircraftModelsBlock.h"

using namespace math_functions;

TransportGraphModel::TransportGraphModel(QList<AirportModel> airports, QString save, double greed, double gregariousness, double cost, double part) {
    this->airports = airports;
    foreach(auto airport, airports) {
        if (maxAirportFlightCount < airport.flightCount) {
            maxAirportFlightCount = airport.flightCount;
        }
    }
    this->greed = greed;
    this->gregariousness = gregariousness;
    this->save = save;
    this->cost = cost;
    this->part = part;
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
    if (save == "s0") {
        for (int i = 0; i < json["aircraftCountKeys"].toArray().count(); i++) {
            aircraftCount[json["aircraftCountKeys"].toArray()[i].toString()] = json["aircraftCountValues"].toArray()[i].toInt();
        }
        allTypesCount = json["allTypesCount"].toInt();
        this->cost = json["cost"].toDouble();
    }
    midPassCount = json["midPassCount"].toDouble();
    this->part = json["part"].toDouble();
    this->midTime = json["midTime"].toDouble();
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
    json["greed"] = (double) greed;
    json["gregariousness"] = (double) gregariousness;
    json["save"] = save;
    if (save == "s0") {
        auto aircraftCountKeys = QJsonArray();
        auto aircraftCountValues = QJsonArray();
        foreach(auto key, aircraftCount.keys()) {
            aircraftCountKeys.append(key);
            aircraftCountValues.append(aircraftCount[key]);
        }
        json["aircraftCountKeys"] = aircraftCountKeys;
        json["aircraftCountValues"] = aircraftCountValues;
        json["allTypesCount"] = allTypesCount;
        json["cost"] = cost;
    }
    json["midPassCount"] = midPassCount;
    json["part"] = part;
    json["midTime"] = midTime;
    return json;
}

void TransportGraphModel::calcDataForView() {
    QHash<QString, QList<double>> lines;
    QHash<QString, double> lineCount;
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
                lineCount[lineId] = airport.connectedPassCount[connectedAirportId];
                if (lineCount[lineId] > lineMaxCount) lineMaxCount = lineCount[lineId];
            }
        }
    }
    viewLines = lines.values();
    viewLinesPassCount = lineCount.values();
    lineMaxCount = 0.05 * lineMaxCount;
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
    auto maxPass = 0;
    allTypesCount = 0.0;
    foreach(auto a, airports) {
        passCount += a.passengersCountOut + a.passengersCountIn;
        allIn += a.passengersCountIn;
        allOut += a.passengersCountOut;
        if (a.passengersCountOut + a.passengersCountIn > maxPass) {
            maxPass = a.passengersCountIn + a.passengersCountOut;
            mainTransportNode = a;
        }
    }
    passCountPieChart.append(
        ChartLine(
                QList<QString>({colorPrimary(), colorSecondary()}),
                QList<double>({(double) allOut, (double)  allIn}),
                QList<QString>({"В аэропорты", "Из аэропортов"})
        )
    );

    auto aircraftModelsBlock = AircraftModelsBlock();
    auto count = 0;
    if (airports.size() > 0) {
        foreach (auto a, airports) {
            // определение коэффициента непрямолинейности
            if (a.id != mainTransportNode.id && !a.connectedAirports.isEmpty() && hasConnection(a.id, mainTransportNode.id)) {
                auto flightDistance = distanceInKm(a.lon, a.lat, mainTransportNode.lon, mainTransportNode.lat);
                auto realDistance = pathSize(findPath(a.id, mainTransportNode.id));
                midFlightDistance += flightDistance;
                midRealDistance += realDistance;
                count++;
            }
            // складывание дистанций маршрутов
            foreach(auto connected, a.connectedAirports) {
                auto connectedAirport = findAirport(connected);
                auto flightDistance = distanceInKm(a.lon, a.lat, connectedAirport.lon, connectedAirport.lat);
                sumDistance += flightDistance;

                if (save != "s0") {
                    auto connectedAirport = findAirport(connected);
                    auto passCount = a.connectedPassCount[connected];
                    auto optimalAircraft = aircraftModelsBlock.getOptimalAircraft(flightDistance, connected, (int) passCount);
                    auto optimalAircraftCount = (int) (passCount / optimalAircraft.seatsCount);
                    if (aircraftCount.contains(optimalAircraft.model)) {
                        aircraftCount[optimalAircraft.model] += optimalAircraftCount;
                    } else {
                        aircraftCount[optimalAircraft.model] = optimalAircraftCount;
                    }
                    allTypesCount += optimalAircraftCount;
                    cost += flightDistance * optimalAircraft.kilometerCost * optimalAircraftCount;
                }

                totalPassCount += a.connectedPassCount[connected];
            }
            totalPassCountInOut += a.passengersCountOut + a.passengersCountIn;
        }
    }
    midFlightDistance /= count;
    midRealDistance /= count;
    nonStraightness = midRealDistance / midFlightDistance;

    qDebug() << "TransportGraphModel" << save
             << "-> allTypesCount =" << allTypesCount
             << "totalPassCount =" << QString::number(totalPassCount / 1000) + "K"
             << "totalPassCountInOut =" << QString::number(totalPassCountInOut / 1000) + "K";
}

QList<AnalyticsRow> TransportGraphModel::getRows(bool isSingle) {
    QList<AnalyticsRow> rows;
    bool isZeroSave = save == "s0";
    if (viewLines.isEmpty()) {
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell *>({
                    new TitleAnalyticsCell("Результаты вычислений графа " + save),
            }), true)
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell *>({
                new NumberAnalyticsCell("Граф еще не посчитан","Чтобы посчитать укажите параметры и нажмите кнопку", colorRed()),
            }))
        );
    } else {
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell *>({
                new TitleAnalyticsCell("Результаты вычислений графа " + save),
            }), true)
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell *>({
                    new NumberAnalyticsCell(mainTransportNode.id,"Главный транспортный узел", colorSecondary()),
                    new NumberAnalyticsCell(QString::number(airports.count()),"Количество аэропортов", colorSecondary()),
                    new NumberAnalyticsCell(QString::number(viewLines.size()),"Количество связей", colorPrimary()),
            }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell *>({
                new NumberAnalyticsCell(isZeroSave ? "Не указано" : QString::number(greed, 'f', 2),"Жадность", isZeroSave ? colorRed() : colorPrimary()),
                new NumberAnalyticsCell(isZeroSave ? "Не указано" : QString::number(gregariousness, 'f', 2),"Стадность", isZeroSave ? colorRed() : colorPrimary()),
                new NumberAnalyticsCell(QString::number(midTime, 'f', 3) + " ч","Средняя доступность", colorPrimary()),
            }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell *>({
                new NumberAnalyticsCell(QString::number(midFlightDistance, 'f', 1),"Cреднее расстояние до главного транспортного узла", colorPrimary()),
                new NumberAnalyticsCell(QString::number(midRealDistance, 'f', 1),"Cредняя длина маршрута до главного транспортного узла", colorPrimary()),
                new NumberAnalyticsCell(QString::number(nonStraightness, 'f', 4),"Коэффициент непрямолинейности", colorPrimary()),
            }))
        );
    }
    if (isSingle) {
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new EmptyAnalyticsCell(),
           }), true)
        );
    }

    return rows;
}

QList<QString> TransportGraphModel::findPath(QString from, QString to) {
    auto fromAirport = findAirport(from);
    auto toAirport = findAirport(to);

    auto frontier = PriorityQueue<QString>();
    frontier.put(from, 0.0);

    auto cameFrom = QHash<QString, QString>();
    auto costSoFar = QHash<QString, double>();
    cameFrom[from] = nullptr;
    costSoFar[from] = 0.0;

    while (frontier.isNotEmpty()) {
        auto current = frontier.get();
        if (current == to) break;

        foreach(auto next, findAirport(current).connectedAirports) {
            if (current != next) {
                auto currentAirport = findAirport(current);
                auto nextAirport = findAirport(next);
                auto newCost = costSoFar[current] +
                               distanceInKm(currentAirport.lon, currentAirport.lat, nextAirport.lon, nextAirport.lat);

                if (!costSoFar.contains(next) || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost + distanceInKm(toAirport.lon, toAirport.lat, currentAirport.lon,
                                                             currentAirport.lat);
                    frontier.put(next, newCost);
                    cameFrom[next] = current;
                }
            }
        }

        if (cameFrom.size() >= airports.size() - 3) return { from, to };
    }

    return reconstructPath(cameFrom, from, to);
}

QList<QString> TransportGraphModel::reconstructPath(QHash<QString, QString> cameFrom, QString from, QString to) {
    auto current = to;
    auto path = QList<QString> { current };
    while (current != from) {
        current = cameFrom[current];
        path.append(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

double TransportGraphModel::pathSize(QList<QString> path) {
    auto distance = 0.0;
    for(int i = 0; i < path.size() - 1; i++) {
        auto from = findAirport(path[i]);
        auto to = findAirport(path[i + 1]);
        distance += distanceInKm(from.lon, from.lat, to.lon, to.lat);
    }
    return distance;
}

bool TransportGraphModel::hasConnection(QString from, QString to, QList<QString> visited) {
    visited.append(from);
    if (from == to) return true;
    bool connected = false;
    auto fromAirport = findAirport(from);
    foreach(auto next, fromAirport.connectedAirports) {
        if (!visited.contains(next)) {
            if (hasConnection(next, to, visited)) {
                return true;
            }
        }
    }
    return false;
}

void TransportGraphModel::setAircraftCount(QHash<QString, int> aircraftCount) {
    this->aircraftCount = aircraftCount;
    foreach(auto count, aircraftCount.values()) {
        allTypesCount += count;
    }
}

double TransportGraphModel::crit(
        bool isHub,
        double plot,
        double maxNonStraightness,
        double minNonStraightness,
        double maxPlot,
        double minPlot,
        double maxMidTime
) {
    auto p1 = isHub ? (1 / plot) / minPlot : plot / maxPlot;
    auto p2 = isHub ? nonStraightness / maxNonStraightness : (1 / nonStraightness) / minNonStraightness;
    auto p3 = (1 / midTime) / maxMidTime;
    return pow(p1, 0.333) * pow(p2, 0.33) * pow(p3, 0.33);
}