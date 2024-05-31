//
// Created by Леонид Соляной on 15.05.2024.
//

#ifndef AVIA_AIRCRAFT_H
#define AVIA_AIRCRAFT_H

#include <QString>

/**
 * Модель описывающая самолет.
 * Используется для определения потока
 * пассажиров через аэропорты и для определения
 * оптимальноко парка самолетов.
 */
class Aircraft {

public:

    /// сокращенное название модели
    QString model;
    /// полное название модели
    QString modelName;
    /// количество кресел
    int seatsCount;
    /// кидлметровая стоимость пассажироместа
    double kilometerCost;
    /// крейсерская скорость
    double speed;
    /// дальность полета
    double range;
    /// используется ли при вычислении
    bool use;
    /// требуемая длина ВПП
    double vppLen;

    Aircraft(
            QString model,
            QString modelName,
            int seatsCount,
            double kilometerCost,
            double speed,
            double range,
            bool use,
            double vppLen
    ) {
        this->model = model;
        this->modelName = modelName;
        this->seatsCount = seatsCount;
        this->kilometerCost = kilometerCost * seatsCount;
        this->speed = speed;
        this->range = range;
        this->use = use;
        this->vppLen = vppLen;
    }
};

#endif //AVIA_AIRCRAFT_H
