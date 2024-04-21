//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateAreaWorker.h"

#include <QDebug>

void CalculateAreaWorker::run() {

    // место для кода Егора

    qDebug() << "CalculateAreaWorker все посчитал";

    emit resultReady();
}
