//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_CHARTLINE_H
#define AVIA_CHARTLINE_H

#include <QString>
#include <QList>

class ChartLine {

public:
    QList<QString> colors;
    QList<double> values;
    QList<QString> name;
    QList<double> valuesByX;

    ChartLine(
        QList<QString> colors,
        QList<double> values,
        QList<QString> name,
        QList<double> valuesByX = QList<double>()
    ) {
        this->colors = colors;
        this->values = values;
        this->name = name;
        this->valuesByX = valuesByX;
    }
};

#endif //AVIA_CHARTLINE_H
