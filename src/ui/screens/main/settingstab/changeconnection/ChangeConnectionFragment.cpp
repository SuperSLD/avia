//
// Created by Леонид Соляной on 20.03.2024.
//

#include <QLabel>
#include "ChangeConnectionFragment.h"
#include "src/ui/common/widgets/button/Button.h"
#include "src/ui/common/widgets/textedit/TextEdit.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

ChangeConnectionFragment::ChangeConnectionFragment() {
    QHBoxLayout *hContainer = new QHBoxLayout;
    QVBoxLayout *vContainer = new QVBoxLayout;
    hContainer->setAlignment(Qt::AlignHCenter);
    hContainer->addLayout(vContainer);
    vContainer->setAlignment(Qt::AlignVCenter);

    QLabel *titleLabel = new QLabel("Настройка подключения");
    titleLabel->setMinimumWidth(650);
    textStyle("titleLabel", titleLabel, 24, colorBlack(), true);
    vContainer->addWidget(titleLabel);

    QLabel *descriptionLabel = new QLabel("Настройка подключения к базе данных с которой в дальнейшем будет проходить работа. Пароль сохранится не самым безопасным образом, но не будет отображаться в приожении.");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setMaximumWidth(650);
    textStyle("descriptionLabel", descriptionLabel, 18, colorTextGray());
    vContainer->addWidget(descriptionLabel);

    ipEdit = new TextEdit("ipEdit", "IP базы данных");
    ipEdit->setMaximumWidth(650);
    ipEdit->setText(settingsRep->getConnectionIp());
    vContainer->addWidget(ipEdit);

    passwordEdit = new TextEdit("passwordEdit", "Пароль");
    passwordEdit->setMaximumWidth(650);
    vContainer->addWidget(passwordEdit);

    QHBoxLayout *buttonContainer = new QHBoxLayout;
    buttonContainer->setAlignment(Qt::AlignRight);
    buttonContainer->setContentsMargins(0, 0, 0, 0);
    vContainer->addLayout(buttonContainer);

    Button *backButton = new Button("backButton", "Назад", false);
    buttonContainer->addWidget(backButton);
    connect(backButton, &Button::clicked, this, &ChangeConnectionFragment::onBack);
    Button *confirmButton = new Button("backButton", "Сохранить", true);
    buttonContainer->addWidget(confirmButton);
    connect(confirmButton, &Button::clicked, this, &ChangeConnectionFragment::onSave);

    coloredCardStyle("ChangeConnectionFragment", this, colorWhite(), 0, 0, 0);
    this->setLayout(hContainer);
}

ChangeConnectionFragment::~ChangeConnectionFragment() {
    delete settingsRep;
}

void ChangeConnectionFragment::onBack() {
    emit back();
}

void ChangeConnectionFragment::onSave() {
    settingsRep->setConnectionIp(ipEdit->text());
    settingsRep->setConnectionPassword(passwordEdit->text());
    emit back();
}
