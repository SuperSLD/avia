//
// Created by Леонид Соляной on 01.05.2024.
//

#include "LoadSavedDataWorker.h"

void LoadSavedDataWorker::run() {
    auto area = Area(settingsRepository->getJson("area"));
    emit areaLolad(area);
    auto graph = TransportGraphModel(settingsRepository->getJson("airports"));
    emit airportsLolad(graph, false);
}
