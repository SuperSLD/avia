//
// Created by Леонид Соляной on 10.04.2024.
//

#include <QVBoxLayout>
#include <QLabel>
#include "NumberCellWidget.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

NumberCellWidget::NumberCellWidget(QString value,
                                   QString name,
                                   QString color) {
    auto *vContainer = new QVBoxLayout;
    vContainer->setAlignment(Qt::AlignHCenter);
    vContainer->setSpacing(24);
    vContainer->setContentsMargins(24, 24, 24, 24);
    auto *numberLabel = new QLabel(value);
    auto *nameLabel = new QLabel(name);

    vContainer->addWidget(numberLabel);
    textStyle("numberLabel", numberLabel, 48, color, true);
    numberLabel->setAlignment(Qt::AlignCenter);
    vContainer->addWidget(nameLabel);
    textStyle("nameLabel", nameLabel, 20, colorBlack());
    nameLabel->setWordWrap(true);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setMinimumWidth(300);
    nameLabel->setMinimumHeight(50);

    coloredCardStyle("NumberCellWidget", this, colorWhite(), 24, 0, 1, colorBorder());
    this->setLayout(vContainer);
}

NumberCellWidget::~NumberCellWidget() {

}
