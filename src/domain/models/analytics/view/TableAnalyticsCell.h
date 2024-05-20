//
// Created by Леонид Соляной on 15.05.2024.
//

#ifndef AVIA_TABLEANALYTICSCELL_H
#define AVIA_TABLEANALYTICSCELL_H

#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/table/TableCellWidget.h"

/**
 * Ячейка аналитики с таблицей.
 */
class TableAnalyticsCell: public BaseAnalyticsCell {

public:
    QList<QList<QString>> table;
    bool firstIsBig;

    /**
     * Ячейка аналитики с таблицей.
     *
     * Когда использовать:
     * Использовать в случае, когда нужно отобразить большое
     * количество данных в одной таблице. Удивительно)
     *
     * Пример использования:
     * new TableAnalyticsCell(aircraftModelsTable, true),
     * new TableAnalyticsCell(aircraftModelsTable),
     *
     * @param table таблица строковых значений, которая будет
     *              отображаться в аналитике.
     * @param firstIsBig устанавливает размер первого столбца.
     *                   нужно в случае, когда в начальном столбце
     *                   не помещается текст.
     */
    TableAnalyticsCell(
            QList<QList<QString>> table,
            bool firstIsBig = false
    ) {
        this->table = table;
        this->firstIsBig = firstIsBig;
    }

    TableAnalyticsCell() {}

    QWidget *getView() override {
        return new TableCellWidget(table, firstIsBig);
    }
};

#endif //AVIA_TABLEANALYTICSCELL_H
