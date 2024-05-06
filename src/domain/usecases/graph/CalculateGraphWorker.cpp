//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateGraphWorker.h"

#include <QDebug>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "AntOptimisation.h"

using namespace std;


void CalculateGraphWorker::run() {

    // место для кода Дениза

        // Создание исходных данных для аэропортов
        vector<Airport> airports = {
            {10, 15, 0}, // Пример данных для аэропорта 1
            {20, 25, 0}, // Пример данных для аэропорта 2
            {15, 20, 0}  // Пример данных для аэропорта 3
            // Можно добавить больше аэропортов по аналогии
        };

        // Общее количество пассажиров
        int totalPassengers = 100;

        // Запуск муравьиного алгоритма
        AntColonyOptimization aco(airports, totalPassengers);
        aco.distributePassengers();

        // Вывод результатов
        for (int i = 0; i < airports.size(); ++i) {
            cout << "Airport " << i + 1 << " Passengers In: " << airports[i].passengersIn
                << " Passengers Out: " << airports[i].passengersOut
                << " Passengers Currently: " << airports[i].passengersCurrently << endl;
        }

    qDebug() << "CalculateGraphWorker все посчитал";

    emit resultReady();
}
