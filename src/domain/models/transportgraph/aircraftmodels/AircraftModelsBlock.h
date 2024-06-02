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

    double maxCost = -1;
    double maxP1 = -1;
    double maxP2 = -1;
    double maxP3 = -1;

public:
    AircraftModelsBlock();

    /**
     * Определение оценочного количества пассажиров.
     *
     * @param k коэффициент загруженности
     * @param aircraftModel сокращенная модель самолета
     *
     * @return количество пассажиров
     */
    int passengersCount(double k, QString aircraftModel);

    Aircraft getByModel(QString model);

    /**
     * Определение опимального самолета, подходящего для выполнения рейса.
     *
     * @param distance расстояние между аэропортами.
     * @param airportId код аэропорта, который будет принимать рейс.
     *
     * @return модель самолета, подходящего для выполнения рейса.
     */
    Aircraft getOptimalAircraft(double distance, QString airportId, int outPassCount);

    int getAircraftCount();

    QList<QString> getKeys();
};


#endif //AVIA_AIRCRAFTMODELSBLOCK_H
