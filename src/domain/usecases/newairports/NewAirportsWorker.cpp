//
// Created by Леонид Соляной on 03.06.2024.
//

#include "NewAirportsWorker.h"
#include "src/domain/models/area/Area.h"


void NewAirportsWorker::run() {
    qDebug() << "NewAirportsWorker начал считать";

    /// тут считашь

    /// посчитанные зоны доступности
    auto area = Area(settingsRepository->getJson("area"));

    /// пример того как пользоваться муравьиным алгоритмом
//    auto *aco = new AntColonyOptimization(
//            "s5",
//            graph.airports,
//            ?, // жадность выберешь сам
//            ?, // стадность выберешь сам
//            1.0
//    );
//  auto newGraph = aco->distributePassengers();

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

    /// в этом месте меняешь graph на свой граф который у тебя оказался
    /// оптимальным в результате перебора
    ///
    /// после вычислений так сохранишь оптимальный граф
    settingsRepository->setJson("airportss5", graph.toJson());
    /// тут граф передается в интерфейс для отображения
    emit resultReady("s5", graph);
    emit onAllCalculated();
}