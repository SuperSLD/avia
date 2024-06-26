//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_CHARTLINE_H
#define AVIA_CHARTLINE_H

#include <QString>
#include <QList>

/**
 * Линия графика.
 *
 * Оторбажается для каждого типа графика по своему.
 * Согласен, это было хорошим решением, сделать настолько
 * непрозрачную схему.
 */
class ChartLine {

public:
    QList<QString> colors;
    QList<double> values;
    QList<QString> name;
    QList<double> valuesByX;
    QList<QString> valuesName;

    /**
     * Линия графика.
     *
     * Надеюсь не придется использовать это.
     * В случае вопросов писать автору.
     *
     * @param colors
     * @param values
     * @param name
     * @param valuesByX
     * @param valuesName
     */
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
