//
// Created by Леонид Соляной on 08.04.2024.
//

#include "SwgButton.h"

#include <QSize>
#include <QString>
#include <QSvgWidget>
#include <QVBoxLayout>

SwgButton::SwgButton(QString path, QSize size, QString name) {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    QSvgWidget *image = new QSvgWidget(":/resc/resc/" + path + ".svg");
    image->setMaximumSize(size);
    image->setMinimumSize(size);
    mainContainer->addWidget(image);
    mainContainer->setContentsMargins(0,0,0,0);
    image->setStyleSheet("background-color:#00FFFFFF;");
    this->setStyleSheet("border:none; padding:0px; background-color:#00FFFFFF;");
    this->setMinimumSize(size);
    this->setMaximumSize(size);
    this->setLayout(mainContainer);

    if (name != NULL) {
        this->name = name;
        connect(this, &SwgButton::clicked, this, &SwgButton::selfClick);
    }
}

SwgButton::~SwgButton() {

}

void SwgButton::selfClick() {
    emit onClicked(name);
}