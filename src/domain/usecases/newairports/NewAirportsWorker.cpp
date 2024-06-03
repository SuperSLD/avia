//
// Created by Леонид Соляной on 03.06.2024.
//

#include "NewAirportsWorker.h"


void NewAirportsWorker::run() {
    qDebug() << "NewAirportsWorker начал считать";

    /// тут считашь

    /// все вот отсюда
    emit onChangeProgress(8);
    sleep(1);
    emit onChangeProgress(4);
    sleep(1);
    emit onChangeProgress(2);
    sleep(1);
    emit onChangeProgress(1);
    sleep(1);
    /// до сюда надо удалить

    qDebug() << "NewAirportsWorker все посчитал";

    /// после вычислений так сохранишь оптимальный граф
    settingsRepository->setJson("airportss5", graph.toJson());
    /// тут граф меняешь на свой оптимальный
    emit resultReady("s5", graph);
    emit onAllCalculated();
}