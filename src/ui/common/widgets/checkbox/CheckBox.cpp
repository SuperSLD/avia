//
// Created by Леонид Соляной on 02.05.2024.
//

#include <src/ui/theme/AppTheme.h>
using namespace theme;

#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "CheckBox.h"
#include "src/ui/common/widgets/swgbutton/SwgButton.h"

CheckBox::CheckBox(QString text, bool checked) {
    this->isChecked = checked;
    //connect(this, &QPushButton::clicked, this, &CheckBox::selfClick);

    auto *hContainer = new QHBoxLayout();
    hContainer->setContentsMargins(0, 0, 0, 0);

    checkboxOf = new SwgButton("checkbox_of", QSize(24, 24), "of");
    connect(checkboxOf, &SwgButton::onClicked, this, &CheckBox::selfClick);
    hContainer->addWidget(checkboxOf);
    checkboxOn = new SwgButton("checkbox_on", QSize(24, 24), "on");
    connect(checkboxOn, &SwgButton::onClicked, this, &CheckBox::selfClick);
    hContainer->addWidget(checkboxOn);

    if (checked) {
        checkboxOf->hide();
    } else {
        checkboxOn->hide();
    }

    auto *label = new QLabel(text);
    textStyle("label", label, 16, colorBlack(), true);
    hContainer->addWidget(label);
    this->setLayout(hContainer);

    coloredCardStyle("checkbox", this, colorWhite(), 0);
}

void CheckBox::selfClick(QString name) {
    qDebug() << "CheckBox::selfClick";
    isChecked = !isChecked;
    if (isChecked) {
        qDebug() << "CheckBox::selfClick = true";
        checkboxOf->hide();
        checkboxOn->show();
    } else {
        qDebug() << "CheckBox::selfClick = false";
        checkboxOf->show();
        checkboxOn->hide();
    }
    emit onChangeState(isChecked);
}
