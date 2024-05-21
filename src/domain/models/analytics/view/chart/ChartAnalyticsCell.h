//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_CHARTANALYTICSCELL_H
#define AVIA_CHARTANALYTICSCELL_H


#include "src/domain/models/analytics/view/BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/chart/ChartCellWidget.h"
#include "ChartLine.h"

#include <QList>

/**
 * Ячейка с графиком.
 *
 * (самая запарная и загадочная ячейка в аналитической таблице)
 */
class ChartAnalyticsCell: public BaseAnalyticsCell {

public:
    QString type;
    QString name;
    QList<ChartLine> lines;
    bool min = false;

    /**
     * Ячейка с графиком.
     *
     * Используется для отображения графика.
     * Доступные типы графиков:
     * 1) Круговая диаграмма (pie, pie_hide_values)
     *    1.1) Круговая диаграмма с подписями значений (pie).
     *    1.2) Круговая диаграмма без подписей значений (pie_hide_values).
     * 2) Линии (line)
     * 3) Столбцы (bar)
     *
     * Когда использовать:
     * Использовать в случае, когда нужно отобразить график.
     *
     * Пример использования:
     * new ChartAnalyticsCell("bar", "Распределение рейсов", flightCountBarChart),
     * new ChartAnalyticsCell("pie", "Распределение рейсов", flightCountPieChart),
     *
     * @param type тип графика (pie, pie_hide_values, line, bar)
     * @param name название графика
     * @param lines данные для отображения графика.
     *              (смотри ChartLine для подробностей)
     */
    ChartAnalyticsCell(
            QString type,
            QString name,
            QList<ChartLine> lines,
            bool min = false
    ) {
        this->type = type;
        this->name = name;
        this->lines = lines;
        this->min = min;
    }

    ChartAnalyticsCell() {}

    QWidget* getView() override {
        return new ChartCellWidget(type, name, lines, min);
    }
};

#endif //AVIA_CHARTANALYTICSCELL_H
