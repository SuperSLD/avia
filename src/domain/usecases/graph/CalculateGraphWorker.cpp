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
#include "src/domain/models/area/Area.h"

using namespace std;


void CalculateGraphWorker::run() {

    qDebug() << "CalculateGraphWorker начал считать" << greed << gregariousness;

    // Запуск муравьиного алгоритма
    auto *aco = new AntColonyOptimization(
            key,
            graph.airports,
            greed,
            gregariousness,
            passengersPart
    );
    connect(aco, &AntColonyOptimization::changeProgress, this, &CalculateGraphWorker::handleProgress);
    auto newGraph = aco->distributePassengers();

    qDebug() << "CalculateGraphWorker все посчитал";
    auto area = Area(settingsRepository->getJson("area"));
    newGraph.midTime = area.calcTime(newGraph);
    settingsRepository->setJson("airports" + key, newGraph.toJson());

    emit resultReady(key, newGraph);
}
