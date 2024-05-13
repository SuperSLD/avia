//
// Created by Леонид Соляной on 12.05.2024.
//

#include "EmptyCellWidget.h"
#include <src/ui/theme/AppTheme.h>
using namespace theme;

EmptyCellWidget::EmptyCellWidget() {
    this->setMinimumHeight(1000);
    coloredCardStyle("TitleCellWidget", this, colorWhite(), 24, 0);
}