//
// Created by Леонид Соляной on 22.04.2024.
//

#ifndef AVIA_AIRCRAFTMODELSBLOCK_H
#define AVIA_AIRCRAFTMODELSBLOCK_H


#include <QHash>
#include "Aircraft.h"

/**
 * Блок отвечающий за вычисления связанные с моделями самолетов.
 * Используется для определения количества пассажиров на рейсе
 * и для определения оптимального самолета, который нужно
 * поставить на рейс.
 */
class AircraftModelsBlock {

private:
    QList<Aircraft> aircraftList;
    int middleCount = 0;

    QHash<QString, double> vppInfo;

public:
    AircraftModelsBlock();

    /**
     * Определение оценочного количества пассажиров.
     *
     * @param k коэффициент загруженности
     * @param aircraftModel сокращенная модель самолета
     * @return количество пассажиров
     */
    int passengersCount(double k, QString aircraftModel);

    Aircraft getByModel(QString model);

    /**
     * Определение опимального самолета, подходящего для выполнения рейса.
     * @param distance расстояние между аэропортами.
     * @param passCount перевозимое количество пассажиров.
     * @return модель самолета, подходящего для выполнения рейса.
     */
    Aircraft getOptimalAircraft(double distance, double passCount);
};


#endif //AVIA_AIRCRAFTMODELSBLOCK_H
