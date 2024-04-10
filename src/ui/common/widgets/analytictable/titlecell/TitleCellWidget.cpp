//
// Created by Леонид Соляной on 11.04.2024.
//

#include <QVBoxLayout>
#include <QLabel>
#include "TitleCellWidget.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

TitleCellWidget::TitleCellWidget(QString title) {
    auto *vContainer = new QVBoxLayout;
    vContainer->setAlignment(Qt::AlignHCenter);
    vContainer->setSpacing(24);
    vContainer->setContentsMargins(24, 24, 24, 24);

    auto *titleLabel = new QLabel(title);

    vContainer->addWidget(titleLabel);
    textStyle("titleLabel", titleLabel, 36, colorBlack(), true);

    coloredCardStyle("TitleCellWidget", this, colorWhite(), 24, 0);
    this->setLayout(vContainer);
}
