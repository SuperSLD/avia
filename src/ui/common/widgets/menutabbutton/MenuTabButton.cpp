//
// Created by Леонид Соляной on 05.02.2024.
//

#include "MenuTabButton.h"

#include <QSize>
#include <QString>
#include <QSvgWidget>
#include <QVBoxLayout>
#include <QLabel>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

MenuTabButton::MenuTabButton(
        QString title,
        QString icon,
        QString iconDark,
        int id
) {
    QHBoxLayout *mainContainer = new QHBoxLayout;
    QSvgWidget *image = new QSvgWidget(":/resc/resc/" + (settingsRep.getTheme() ? icon : iconDark) + ".svg");
    squareWidgetStyle(image, 24);
    QLabel *titleLabel = new QLabel(title);
    textStyle("titleLabel", titleLabel, 20, colorBlack());
    mainContainer->addWidget(image);
    mainContainer->addWidget(titleLabel);
    mainContainer->setContentsMargins(16,0,16,0);

    coloredCardStyle("MenuTabButton", this, colorWhite(), 24, 24, 1, colorGray(), colorWhite(), colorPrimary());
    this->setLayout(mainContainer);
    this->id = id;
    connect(this, &MenuTabButton::clicked, this, &MenuTabButton::selfClick);
}

MenuTabButton::~MenuTabButton() {

}

void MenuTabButton::selfClick() {
    emit onClicked(id);
}
