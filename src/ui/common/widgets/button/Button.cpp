//
// Created by Леонид Соляной on 20.03.2024.
//

#include "Button.h"

#include <src/ui/theme/AppTheme.h>
#include <QVBoxLayout>
#include <QLabel>

using namespace theme;

Button::Button(QString id, QString title, bool solid) {
    this->setMinimumHeight(54);
    this->setMinimumWidth(250);
    if (solid) {
        coloredCardStyle(
                id,
                this,
                colorPrimary(),
                16,
                16,
                1,
                colorPrimary(),
                colorTextPrimary(),
                colorTextPrimary()
        );
    } else {
        coloredCardStyle(
                id,
                this,
                colorWhite(),
                16,
                16,
                1,
                colorPrimary(),
                colorWhite(),
                colorTextPrimary()
        );
    }

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->setAlignment(Qt::AlignCenter);
    QLabel *titleLabel = new QLabel(title);
    if (solid) {
        textStyle("titleLabel", titleLabel, 16, colorWhite(), true);
    } else {
        textStyle("titleLabel", titleLabel, 16, colorPrimary(), true);
    }
    buttonLayout->addWidget(titleLabel);
    this->setLayout(buttonLayout);
}

Button::~Button() {

}
