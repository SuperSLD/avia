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
    QList<QString> valuesName;

    ChartLine(
        QList<QString> colors,
        QList<double> values,
        QList<QString> name,
        QList<double> valuesByX = QList<double>(),
        QList<QString> valuesName = QList<QString>()
    ) {
        this->colors = colors;
        this->values = values;
        this->name = name;
        this->valuesByX = valuesByX;
        this->valuesName = valuesName;
    }
};

#endif //AVIA_CHARTLINE_H
