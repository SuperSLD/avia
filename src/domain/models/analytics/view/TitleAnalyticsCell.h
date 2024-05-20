//
// Created by Леонид Соляной on 11.04.2024.
//

#ifndef AVIA_TITLEANALYTICSCELL_H
#define AVIA_TITLEANALYTICSCELL_H

#include <QFrame>
#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/titlecell/TitleCellWidget.h"

/**
 * Ячейка с заголовком.
 */
class TitleAnalyticsCell: public BaseAnalyticsCell {

public:
    QString title;
    bool isSmall;

    /**
     * Ячейка с заголовком.
     *
     * Когда использовать:
     * Использовать в случае, если нужно отделить одни данные
     * от других заголовком.
     *
     * Пример использования:
     * new TitleAnalyticsCell("Результаты вычислений графа " + save)
     *
     * @param title заголовок, отображающийся крупным шрифтоа.
     * @param isSmall true, если заголовок маленький.
     */
    TitleAnalyticsCell(
        QString title,
        bool isSmall = false
    ) {
        this->title = title;
        this->isSmall = isSmall;
    }

    QWidget* getView() override {
        return new TitleCellWidget(title, isSmall);
    }
};

#endif //AVIA_TITLEANALYTICSCELL_H
