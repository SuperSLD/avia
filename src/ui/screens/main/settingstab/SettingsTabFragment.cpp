//
// Created by Леонид Соляной on 18.03.2024.
//

#include "SettingsTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"
#include "src/ui/common/widgets/button/Button.h"
#include "src/ui/common/widgets/switcher/Switcher.h"

#include <QLabel>
#include <QDebug>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

SettingsTabFragment::SettingsTabFragment() {
    this->connector = connector;

    // Tулбар
    QVBoxLayout *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Настройки", "settings", "settings_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QHBoxLayout *contentHContainer = new QHBoxLayout();
    contentFrame->setLayout(contentHContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainContainer->addWidget(contentFrame);
    QVBoxLayout *contentVContainer = new QVBoxLayout();
    contentHContainer->setAlignment(Qt::AlignCenter);
    contentHContainer->addLayout(contentVContainer);
    contentVContainer->setAlignment(Qt::AlignVCenter);

    // Настройка подключения
    QLabel *dbConnectionTitle = new QLabel("Подключение к базе данных");
    textStyle("dbConnectionTitle", dbConnectionTitle, 24, colorBlack(), true);
    dbConnectionTitle->setMinimumWidth(650);
    contentVContainer->addWidget(dbConnectionTitle);

    QLabel *dbConnectionDescription = new QLabel("Путь по которому можно подключиться к удаленной или локальной базе данных");
    textStyle("dbConnectionDescription", dbConnectionDescription, 20, colorTextGray());
    dbConnectionDescription->setMinimumWidth(650);
    dbConnectionDescription->setWordWrap(true);
    contentVContainer->addWidget(dbConnectionDescription);

    QHBoxLayout *dbConnectionButtonContainer = new QHBoxLayout;
    dbConnectionButtonContainer->setAlignment(Qt::AlignRight);
    dbConnectionButtonContainer->setContentsMargins(0, 0, 0, 0);

    QFrame *connectionInfoFrame = new QFrame();
    QVBoxLayout *connectionInfoContainer = new QVBoxLayout();
    connectionInfoContainer->setContentsMargins(24, 24, 24, 24);
    coloredCardStyle("connectionInfoFrame", connectionInfoFrame, colorWhite(), 16, 0, 1, colorBorder());
    connectionInfoFrame->setLayout(connectionInfoContainer);
    contentVContainer->addWidget(connectionInfoFrame);

    ipLabel = new QLabel("localhost::35564");
    QString ip = settingsRep->getConnectionIp();
    QString user = settingsRep->getConnectionUser();
    ipLabel->setText(ip.size() > 1 ? ip + " -> " + user : "Не выбрано");
    textStyle("ipLabel", ipLabel, 20, colorBlack());
    connectionInfoContainer->addWidget(ipLabel);

    mongoLabel = new QLabel("MongoDB");
    textStyle("mongoLabel", mongoLabel, 16, colorPrimary(), true);
    connectionInfoContainer->addWidget(mongoLabel);

    Button *dbConnectionButton = new Button("dbConnectionButton", "Настроить подключение", false);
    dbConnectionButtonContainer->addWidget(dbConnectionButton);
    connect(dbConnectionButton, &Button::clicked, this, &SettingsTabFragment::onDatabaseChangeClicked);
    contentVContainer->addLayout(dbConnectionButtonContainer);

    // Отступ
    QWidget *space = new QWidget();
    space->setMinimumHeight(24);
    contentVContainer->addWidget(space);

    // Настройка темы
    QLabel *themeTitle = new QLabel("Тема приложения");
    textStyle("themeTitle", themeTitle, 24, colorBlack(), true);
    themeTitle->setMinimumWidth(650);
    contentVContainer->addWidget(themeTitle);

    QLabel *themeDescription = new QLabel("Вы можете поменять оформление приложения и выбрать светлую или темную тему");
    textStyle("themeDescription", themeDescription, 20, colorTextGray());
    themeDescription->setMinimumWidth(650);
    themeDescription->setWordWrap(true);
    contentVContainer->addWidget(themeDescription);

    QList<QString> themes = QList<QString>();
    themes.append("Светлая");
    themes.append("Темная");
    Switcher *themeSwitcher = new Switcher("themeSwitcher", themes, settingsRep->getTheme() ? "Светлая" : "Темная");
    connect(themeSwitcher, &Switcher::onVariantSwitched, this, &SettingsTabFragment::onThemeSelected);
    contentVContainer->addWidget(themeSwitcher);
}

SettingsTabFragment::~SettingsTabFragment() {
    delete settingsRep;
    delete ipLabel;
    delete mongoLabel;
}

void SettingsTabFragment::onThemeSelected(QString theme) {
    qDebug() << "SettingsTabFragment: onThemeSelected" << theme;
    settingsRep->setTheme(theme == "Светлая");
    emit onThemeSwitched();
}

void SettingsTabFragment::onDatabaseChangeClicked() {
    emit onDatabaseChange();
}

void SettingsTabFragment::onResume() {
    qDebug() << "SettingsTabFragment: onResume";
    QString ip = settingsRep->getConnectionIp();
    QString user = settingsRep->getConnectionUser();
    ipLabel->setText(ip.size() > 1 ? ip + " -> " + user : "Не выбрано");
    if (connector->isConnected()) {
        textStyle("mongoLabel", mongoLabel, 16, colorPrimary(), true);
    } else {
        textStyle("mongoLabel", mongoLabel, 16, colorRed(), true);
    }
}

void SettingsTabFragment::setConnector(DBConnector *connector) {
    qDebug() << "SettingsTabFragment: setConnector";
    this->connector = connector;
}
