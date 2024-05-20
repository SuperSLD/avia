//
// Created by Леонид Соляной on 11.04.2024.
//

#include <QVBoxLayout>
#include <QLabel>
#include "TitleCellWidget.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

TitleCellWidget::TitleCellWidget(QString title, bool isSmall) {
    auto *vContainer = new QVBoxLayout;
    vContainer->setAlignment(Qt::AlignHCenter);
    vContainer->setSpacing(24);
    vContainer->setContentsMargins(24, 24, 24, 24);

    auto *titleLabel = new QLabel(title);

    vContainer->addWidget(titleLabel);
    if (isSmall) {
        textStyle("titleLabel", titleLabel, 24, colorTextGray(), false);
    } else {
        textStyle("titleLabel", titleLabel, 36, colorBlack(), true);
    }

    coloredCardStyle("TitleCellWidget", this, colorWhite(), 24, 0);
    this->setLayout(vContainer);
}
