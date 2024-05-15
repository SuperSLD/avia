//
// Created by Леонид Соляной on 22.04.2024.
//

#ifndef AVIA_AIRCRAFTMODELSBLOCK_H
#define AVIA_AIRCRAFTMODELSBLOCK_H


#include <QHash>
#include "Aircraft.h"

/**
 * Блок вычисления количества пассажиров на рейсе.
 * На ход подается коэффициент загруженности самолета 0 .. 100 и модель самолета.
 * На выходе получается оценочное количество пассажиров, которые находятся в самолете.
 */
class AircraftModelsBlock {

private:
    QList<Aircraft> aircraftList;
    int middleCount = 0;

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

    /**
     * Определение опимального самолета, подходящего для выполнения рейса.
     * @param distance расстояние между аэропортами.
     * @param passCount перевозимое количество пассажиров.
     * @return модель самолета, подходящего для выполнения рейса.
     */
    Aircraft getOptimalAircraft(double distance, double passCount);
};


#endif //AVIA_AIRCRAFTMODELSBLOCK_H
