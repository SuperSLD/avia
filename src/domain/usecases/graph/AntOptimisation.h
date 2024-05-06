//
// Created by Дениз Вуколов on 06.05.2024.
//

#ifndef ANTOPTIMISATION_H
#define ANTOPTIMISATION_H
using namespace std;
// Структура, представляющая аэропорт
struct Airport {
    int passengersIn;
    int passengersOut;
    int passengersCurrently;
};

// Структура, представляющая ребро в транспортной сети
struct Edge {
    int source;
    int destination;
    int weight;
    bool visited;
};

class AntColonyOptimization {
private:
    vector<Airport> airports;
    vector<Edge> edges;
    int numAirports;
    int numPassengers;

    // Инициализация ребер транспортной сети
    void initializeEdges() {
        // Создаем ребра между всеми парами аэропортов
        for (int i = 0; i < numAirports; ++i) {
            for (int j = i + 1; j < numAirports; ++j) {
                Edge e;
                e.source = i;
                e.destination = j;
                e.weight = rand() % 100 + 1; // Случайный вес ребра
                e.visited = false;
                edges.push_back(e);
            }
        }
    }

    // Выбор следующего непосещенного ребра для распределения пассажиров
    int selectNextEdge() {
        double totalWeight = 0.0;
        for (const auto& edge : edges) {
            if (!edge.visited) {
                totalWeight += 1.0 / edge.weight; // Обратная величина веса
            }
        }

        double randValue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        double cumulativeProbability = 0.0;
        for (int i = 0; i < edges.size(); ++i) {
            if (!edges[i].visited) {
                cumulativeProbability += (1.0 / edges[i].weight) / totalWeight;
                if (randValue <= cumulativeProbability) {
                    return i;
                }
            }
        }
        return -1; // Если все ребра уже посещены
    }

public:
    AntColonyOptimization(vector<Airport> airports, int numPassengers)
        : airports(airports), numAirports(airports.size()), numPassengers(numPassengers) {}

    // Распределение пассажиров с использованием муравьиного алгоритма
    void distributePassengers() {
        // Инициализация ребер
        initializeEdges();

        // Распределение пассажиров по ребрам
        while (numPassengers > 0) {
            int edgeIndex = selectNextEdge();
            if (edgeIndex == -1) {
                break; // Если все ребра уже посещены
            }
            Edge& e = edges[edgeIndex];
            int passengersToTransport = min(numPassengers, e.weight);
            e.visited = true;
            numPassengers -= passengersToTransport;
            airports[e.source].passengersCurrently += passengersToTransport;
            airports[e.destination].passengersCurrently -= passengersToTransport;
        }

        // Сброс использования всех рёбер
        for (auto& edge : edges) {
            edge.visited = false;
        }
    }
};


#endif //ANTOPTIMISATION_H
