//
// Created by Леонид Соляной on 20.03.2024.
//

#include "Button.h"

#include <QVBoxLayout>
#include <QLabel>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

Button::Button(QString id, QString title, bool solid) {
    this->solid = solid;
    this->id = id;
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
    titleLabel = new QLabel(title);
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

void Button::enabled(bool isEnabled) {
    this->isEnabled = isEnabled;
    if (isEnabled) {
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
        if (solid) {
            textStyle("titleLabel", titleLabel, 16, colorWhite(), true);
        } else {
            textStyle("titleLabel", titleLabel, 16, colorPrimary(), true);
        }
    } else {
        if (solid) {
            coloredCardStyle(
                    id,
                    this,
                    colorGray(),
                    16,
                    16,
                    1,
                    colorGray(),
                    colorGray(),
                    colorGray()
            );
        } else {
            coloredCardStyle(
                    id,
                    this,
                    colorGray(),
                    16,
                    16,
                    1,
                    colorGray(),
                    colorGray(),
                    colorGray()
            );
        }
        if (solid) {
            textStyle("titleLabel", titleLabel, 16, colorWhite(), true);
        } else {
            textStyle("titleLabel", titleLabel, 16, colorTextGray(), true);
        }
    }
    this->setEnabled(isEnabled);
}
