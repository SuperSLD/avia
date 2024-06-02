//
// Created by Леонид Соляной on 15.05.2024.
//

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include "TableCellWidget.h"


#include <src/ui/theme/AppTheme.h>
using namespace theme;

TableCellWidget::TableCellWidget(QList<QList<QString>> table, bool firstIsBig) {
    auto *vContainer = new QVBoxLayout;
    vContainer->setSpacing(24);
    vContainer->setContentsMargins(24, 24, 24, 24);

    auto rowIndex = 0;
    foreach(auto row, table) {
        auto cellIndex = 0;
        auto rowContainer = new QHBoxLayout();
        foreach(auto cell, row) {
            auto cellLabel = new QLabel(cell);
            if (firstIsBig && cellIndex == 0) {
                cellLabel->setMinimumWidth(250);
            }
            if (rowIndex == 0) {
                textStyle("cellLabel", cellLabel, 16, colorPrimary(), true);
            } else if (cellIndex == 0) {
                textStyle("cellLabel", cellLabel, 16, colorBlack(), true);
            } else {
                textStyle("cellLabel", cellLabel, 16, colorBlack());
            }
            rowContainer->addWidget(cellLabel);
            cellIndex++;
        }
        vContainer->addLayout(rowContainer);
        rowIndex++;
    }

    coloredCardStyle("NumberCellWidget", this, colorWhite(), 24, 0, 1, colorBorder());
    this->setLayout(vContainer);
}

TableCellWidget::~TableCellWidget() {

}
