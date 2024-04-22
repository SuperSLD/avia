//
// Created by Леонид Соляной on 22.04.2024.
//

#ifndef AVIA_PASSENGERSCOUNTBLOCK_H
#define AVIA_PASSENGERSCOUNTBLOCK_H


#include <QHash>

/**
 * Блок вычисления количества пассажиров на рейсе.
 * На ход подается коэффициент загруженности самолета 0 .. 100 и модель самолета.
 * На выходе получается оценочное количество пассажиров, которые находятся в самолете.
 */
class PassengersCountBlock {

private:
    QHash<QString, int> seatsByType;
    int middleCount = 0;

public:
    PassengersCountBlock();

    /**
     * Определение оценочного количества пассажиров.
     *
     * @param k коэффициент загруженности
     * @param aircraftModel сокращенная модель самолета
     * @return количество пассажиров
     */
    int passengersCount(double k, QString aircraftModel);
};


#endif //AVIA_PASSENGERSCOUNTBLOCK_H
