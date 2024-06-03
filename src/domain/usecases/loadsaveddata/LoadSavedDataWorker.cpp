//
// Created by Леонид Соляной on 01.05.2024.
//

#include "LoadSavedDataWorker.h"

void LoadSavedDataWorker::run() {
    auto area = Area(settingsRepository->getJson("area"));
    if (!area.points.isEmpty()) emit areaLolad(area);
    auto graph = TransportGraphModel(settingsRepository->getJson("airports"));
    if (!graph.airports.isEmpty()) emit airportsLolad(graph, false);

    auto saves = QList<QString> {"s1", "s2", "s3", "s4", "s5"};
    foreach(auto s, saves) {
        auto savedGraph = TransportGraphModel(settingsRepository->getJson("airports" + s));
        if (!savedGraph.airports.isEmpty()) emit graphLoad(s, savedGraph);
    }
}
