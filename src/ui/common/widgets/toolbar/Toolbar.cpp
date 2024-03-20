//
// Created by Леонид Соляной on 18.03.2024.
//

#include <QVBoxLayout>
#include <QLabel>
#include "Toolbar.h"

#include <src/ui/theme/AppTheme.h>
#include <QSvgWidget>

using namespace theme;

Toolbar::Toolbar(QString title, QString icon, QString iconDark) {
    QVBoxLayout *verticalContainer = new QVBoxLayout();
    verticalContainer->setContentsMargins(0, 0, 0 , 0);
    verticalContainer->setSpacing(0);
    QHBoxLayout *horizontalContainer = new QHBoxLayout();
    horizontalContainer->setContentsMargins(16, 16, 16, 16);
    horizontalContainer->setSpacing(16);

    verticalContainer->addLayout(horizontalContainer);

    QSvgWidget *image = new QSvgWidget(":/resc/resc/" + (settingsRep.getTheme() ? icon : iconDark) + ".svg");
    squareWidgetStyle(image, 36);
    horizontalContainer->addWidget(image);

    QLabel *titleLabel = new QLabel(title);
    textStyle("titleLabel", titleLabel, 24, colorBlack(), true);
    horizontalContainer->addWidget(titleLabel);

    QWidget *line = new QWidget();
    line->setMinimumHeight(1);
    line->setMaximumHeight(1);
    coloredCardStyle("line", line, colorBorder(), 0, 0);
    verticalContainer->addWidget(line);

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    this->setLayout(verticalContainer);
}

Toolbar::~Toolbar() {

}
