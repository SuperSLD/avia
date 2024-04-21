//
// Created by Леонид Соляной on 17.04.2024.
//

#include "CalculateGraphWorker.h"

#include <QDebug>

void CalculateGraphWorker::run() {

    // место для кода Дениза

    qDebug() << "CalculateGraphWorker все посчитал";

    emit resultReady();
}
