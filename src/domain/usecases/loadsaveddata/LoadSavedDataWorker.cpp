//
// Created by Леонид Соляной on 01.05.2024.
//

#include "LoadSavedDataWorker.h"

void LoadSavedDataWorker::run() {
    auto area = Area(settingsRepository->getJson("area"));
    emit areaLolad(area);
    auto graph = TransportGraphModel(settingsRepository->getJson("airports"));
    emit airportsLolad(graph, false);

    auto saves = QList<QString> {"s1", "s2", "s3", "s4"};
    foreach(auto s, saves) {
        emit graphLoad(s, settingsRepository->getJson("airports" + s));
    }
}
