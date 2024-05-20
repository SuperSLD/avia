//
// Created by Леонид Соляной on 12.05.2024.
//

#ifndef AVIA_EMPYANALYTICSCELL_H
#define AVIA_EMPYANALYTICSCELL_H

#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/empty/EmptyCellWidget.h"

/**
 * Пустая ячейка аналитики.
 *
 * Когда использовать:
 * Использовать для заполнения пустого пространства под данными.
 *
 * Пример использования:
 * if (isSingle) {
 *      rows.append(
 *          AnalyticsRow(QList<BaseAnalyticsCell*>({
 *                 new EmptyAnalyticsCell(),
 *         }), true)
 *      );
 * }
 *
 * Отображается в местах, где под данными нужно сделать отсуп.
 * Это нужно так как скрол элемент не дает поменять его фон.
 */
class EmptyAnalyticsCell: public BaseAnalyticsCell {

public:
    EmptyAnalyticsCell() {}

    QWidget* getView() override {
        return new EmptyCellWidget();
    }
};

#endif //AVIA_EMPYANALYTICSCELL_H
