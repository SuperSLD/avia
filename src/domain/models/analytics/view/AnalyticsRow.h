//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_ANALYTICSROW_H
#define AVIA_ANALYTICSROW_H

#include <QString>
#include <QList>
#include <QFrame>
#include "src/domain/models/analytics/view/NumberAnalyticsCell.h"

#include <src/ui/theme/AppTheme.h>
#include <QHBoxLayout>

using namespace theme;

/**
 * Строка аналитической таблицы.
 *
 * Содержит в себе список BaseAnalyticsCell и
 * отображает их по очереди. Этот клас не нужно трогать.
 */
class AnalyticsRow {

public:

    QList<BaseAnalyticsCell *> cells;
    bool alignLeft;

    /**
     * Строка аналитической таблицы.
     *
     * @param cells ячейки строки таблицы аналитики.
     * @param alignLeft сдвигает все содержимое влево.
     *                  По умолчанию ячейки занимают все свободное пространство.
     */
    AnalyticsRow(
        QList<BaseAnalyticsCell *> cells,
        bool alignLeft = false
    ) {
        this->cells = cells;
        this->alignLeft = alignLeft;
    }

    QFrame* getRowView() {
        auto *frame = new QFrame;
        coloredCardStyle("frame", frame, colorWhite(), 0, 0);

        auto *container = new QHBoxLayout;
        container->setContentsMargins(24, 12, 24, 12);
        container->setSpacing(16);
        foreach(BaseAnalyticsCell *cell, cells) {
            container->addWidget(cell->getView());
        }
        frame->setLayout(container);
        if (alignLeft) {
            container->setAlignment(Qt::AlignLeft);
        }

        return frame;
    }
};

#endif //AVIA_ANALYTICSROW_H
