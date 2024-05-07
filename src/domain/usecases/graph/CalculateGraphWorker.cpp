//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateGraphWorker.h"

#include <QDebug>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "AntOptimisation.h"

using namespace std;


void CalculateGraphWorker::run() {

    QList<Airport> airports;

    // Общее количество пассажиров
    int totalPassengers = 0;

    foreach(auto a, graph.airports) {
        int pIn = (int) (a.passengersCountIn * 0.001);
        int pOut = (int) (a.passengersCountOut * 0.001);
        airports.append(
            {
                a.id,
                a.lon,
                a.lat,
                pIn,
              pOut,
                pIn + pOut
            }
        );
        totalPassengers += pIn + pOut;
    }

    // Запуск муравьиного алгоритма
    auto *aco = new AntColonyOptimization(
            airports.toVector().toStdVector(),
            totalPassengers,
            graph.airports,
            greed,
            gregariousness
    );
    connect(aco, &AntColonyOptimization::changeProgress, this, &CalculateGraphWorker::handleProgress);
    auto newGraph = aco->distributePassengers();

    qDebug() << "CalculateGraphWorker все посчитал";

    settingsRepository->setJson("airports" + key, newGraph.toJson());

    emit resultReady(key, newGraph);
}
