//
// Created by Дениз Вуколов on 06.05.2024.
//

#ifndef ANTOPTIMISATION_H
#define ANTOPTIMISATION_H


#include "src/domain/usecases/math/geometry.h"
using namespace geometry;
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
};

class AntColonyOptimization: public QObject {
    Q_OBJECT;
public:

    QList<AirportModel> originalAirports;
    vector<Airport> airports;
    vector<Edge> edges;
    int numAirports;
    int numPassengers;

    /// жадность
    double greed = 1;
    /// стадность
    double gregariousness = 1;

    AntColonyOptimization(vector<Airport> airports, int numPassengers, QList<AirportModel> original, double greed, double gregariousness)
        : airports(airports), numAirports(airports.size()), numPassengers(numPassengers), originalAirports(original), greed(greed), gregariousness(gregariousness) {}

    // Инициализация ребер транспортной сети
    void initializeEdges() {
        // Создаем ребра между всеми парами аэропортов
        for (int i = 0; i < numAirports; ++i) {
            for (int j = i + 1; j < numAirports; ++j) {
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
    }

    double probability(Edge edge) {
        double sum;
        foreach(auto e, edges) {
            sum += pow(e.weight, greed) * pow(e.pheromone, gregariousness);
        }
        return (pow(edge.weight, greed) * pow(edge.pheromone, gregariousness)) / sum;
    }

    // Выбор следующего непосещенного ребра для распределения пассажиров
    int selectNextEdge() {
        double maxP = 0;
        double maxPEdge = -1;
        for (int i = 0; i < edges.size(); i++) {
            if (airports[edges[i].source].passengersOut > 0 && airports[edges[i].destination].passengersIn > 0) {
                auto p = probability(edges[i]);
                if (maxP < p) {
                    maxP = p;
                    maxPEdge = i;
                }
            }
        }
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

            int count = 200;
            int passengersToTransport = min(count, airports[edge.source].passengersOut);
            numPassengers -= passengersToTransport;
            airports[edge.source].passengersOut -= passengersToTransport;
            airports[edge.destination].passengersIn += passengersToTransport;

            emit changeProgress(numPassengers);
            qDebug() << "distributePassengers transport =" << passengersToTransport << "all" << numPassengers;
            qDebug() << airports[edge.source].id << "->" << airports[edge.destination].id;
            qDebug() << airports[edge.source].passengersOut << "->" << airports[edge.destination].passengersIn;
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
                originalAirports[airportTo].addConnection(from);
            }
        }
        return TransportGraphModel(originalAirports, greed, gregariousness);
    }

signals:
    void changeProgress(int progress);
};


#endif //ANTOPTIMISATION_H
