//
// Created by Дениз Вуколов on 06.05.2024.
//

#ifndef ANTOPTIMISATION_H
#define ANTOPTIMISATION_H

#include "src/domain/models/transportgraph/aircraftmodels/AircraftModelsBlock.h"
#include "src/domain/usecases/math/math_functions.h"
using namespace math_functions;
using namespace std;
#include <QDebug>

// Структура, представляющая аэропорт
struct Airport {
    QString id;
    double lon;
    double lat;
    int passengersIn;
    int passengersOut;
    int passengersCurrently;
};

// Структура, представляющая ребро в транспортной сети
struct Edge {
    int source;
    int destination;
    double weight;
    double pheromone;
    bool visited;
    int passCount = 0;
};

class AntColonyOptimization: public QObject {
    Q_OBJECT;
public:

    QString save;
    QList<AirportModel> originalAirports;
    std::vector<Airport> airports;
    std::vector<Edge> edges;
    int numAirports;
    int numPassengers;

    /// часть распределяемых пассажиров
    double part;
    /// жадность
    double greed = 1;
    /// стадность
    double gregariousness = 1;

    AntColonyOptimization(QString save, std::vector<Airport> airports, int numPassengers, QList<AirportModel> original, double greed, double gregariousness, double part)
        : save(save), airports(airports), numAirports(airports.size()), numPassengers(numPassengers / 2), originalAirports(original), greed(greed), gregariousness(gregariousness), part(part) {}

    // Инициализация ребер транспортной сети
    void initializeEdges() {
        // Создаем ребра между всеми парами аэропортов
        for (int i = 0; i < airports.size(); ++i) {
            for (int j = i + 1; j < airports.size(); ++j) {
                auto d = distanceInKm(
                    airports[i].lon, airports[i].lat,
                    airports[j].lon, airports[j].lat
                );
                Edge e;
                e.source = i;
                e.destination = j;
                e.weight = 1 / d; //rand() % 100 + 1; // Случайный вес ребра
                e.pheromone = 1 / d;
                e.visited = false;
                edges.push_back(e);
            }
        }
        qDebug() << "Количество проинициализированных ребер" << edges.size();
    }

    double sum = -1.0;

    double probability(Edge edge) {
        if (sum < 0) {
            sum = 0.0;
            foreach(auto e, edges) {
                sum += pow(e.weight, greed) * pow(e.pheromone, gregariousness);
            }
        }
        return (pow(edge.weight, greed) * pow(edge.pheromone, gregariousness)) / sum;
    }

    // Выбор следующего непосещенного ребра для распределения пассажиров
    int selectNextEdge() {
        sum = -1.0;
        double sumP = 0;
        double maxPEdge = -1;
        QHash<int, double> pList;
        for (int i = 0; i < edges.size(); i++) {
            auto distance = distanceInKm(
                airports[edges[i].source].lon, airports[edges[i].source].lat,
                airports[edges[i].destination].lon, airports[edges[i].destination].lat
            );
            if (airports[edges[i].source].passengersOut > 0 && airports[edges[i].destination].passengersIn > 0 && distance > 100) {
                auto p = probability(edges[i]);
                pList[i] = p;
                sumP += p;
            }
        }
        auto randVal = randInRange(0.0, sumP);
        foreach(int key, pList.keys()) {
            randVal -= pList[key];
            if (randVal < 0) {
                maxPEdge = key;
                break;
            }
        }
        if (maxPEdge < 0) return maxPEdge;
        auto edge = edges[maxPEdge];
        auto d = distanceInKm(
                airports[edge.destination].lon, airports[edge.destination].lat,
                airports[edge.source].lon, airports[edge.source].lat
        );
        edges[maxPEdge].pheromone += 1 / d;
        edges[maxPEdge].visited = true;
        return maxPEdge;
    }

    // Распределение пассажиров с использованием муравьиного алгоритма
    TransportGraphModel distributePassengers() {
        // Инициализация ребер
        initializeEdges();

        // Распределение пассажиров по ребрам
        while (numPassengers > 0) {
            auto edgeIndex = selectNextEdge();
            if (edgeIndex < 0) {
                qDebug() << "distributePassengers -1 index";
                return createGraph();
            }
            auto edge = edges[edgeIndex];

            int count = 100;
            int passengersToTransport = min(count, airports[edge.source].passengersOut);
            numPassengers -= passengersToTransport;
            edges[edgeIndex].passCount += passengersToTransport;
            airports[edge.source].passengersOut -= passengersToTransport;
            airports[edge.destination].passengersIn += passengersToTransport;

            emit changeProgress(numPassengers);
        }

        return createGraph();
    }

    TransportGraphModel createGraph() {
        foreach(auto a, originalAirports) {
            a.connectedAirports = QList<QString>();
        }
        foreach(auto e, edges) {
            if (e.visited) {
                auto from = airports[e.source].id;
                auto to = airports[e.destination].id;
                int airportFrom = 0;
                int airportTo = 0;
                for (int i = 0; i < originalAirports.size(); i++) {
                    if (originalAirports[i].id == from) {
                        airportFrom = i;
                    }
                    if (originalAirports[i].id == to) {
                        airportTo = i;
                    }
                }
                originalAirports[airportFrom].addConnection(to);
                originalAirports[airportFrom].connectedPassCount[to] = e.passCount;
                originalAirports[airportTo].addConnection(from);
                originalAirports[airportTo].connectedPassCount[from] = e.passCount;
            }
        }
        auto graph = TransportGraphModel(originalAirports, save, greed, gregariousness, 0, part);
        return graph;
    }

signals:
    void changeProgress(int progress);
};


#endif //ANTOPTIMISATION_H
