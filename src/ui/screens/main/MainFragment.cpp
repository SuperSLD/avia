//
// Created by Леонид Соляной on 03.02.2024.
//

#include "MainFragment.h"
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QLabel>

#include <src/ui/common/widgets/menutabbutton/MenuTabButton.h>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

#include "src/ui/fragmentfactory/FragmentFactoryImpl.h"
using namespace screens;

MainFragment::MainFragment() {
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    mainHLayout->setContentsMargins(0,0,0,0);

    // Центральный контейнер
    QHBoxLayout *centerContainer = new QHBoxLayout;
    mainHLayout->addLayout(centerContainer);
    centerContainer->setContentsMargins(0,0,0,0);

    // Контейрен меню ========================================================================
    QFrame *menuFrame = new QFrame;
    QVBoxLayout *menuContainer = new QVBoxLayout;
    menuContainer->setContentsMargins(0,0,0,0);
    centerContainer->addWidget(menuFrame);
    menuContainer->setAlignment(Qt::AlignTop);
    menuFrame->setLayout(menuContainer);
    whiteCardStyle("menuFrame", menuFrame);
    menuFrame->setMinimumWidth(403);
    menuFrame->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);

    // Плашка с выбранной бд
    QFrame *dbInfoFrame = new QFrame;
    QHBoxLayout *dbInfoContainer = new QHBoxLayout;
    dbInfoContainer->setContentsMargins(0,0,0,0);
    dbInfoFrame->setLayout(dbInfoContainer);
    menuContainer->addWidget(dbInfoFrame);
    coloredCardStyle("dbInfoFrame", dbInfoFrame, colorPrimary(), 24);
    dbInfoFrame->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);
    QSvgWidget *dbIcon = new QSvgWidget(":/resc/resc/db_icon.svg");
    dbInfoContainer->addWidget(dbIcon);
    squareWidgetStyle(dbIcon, 48);
    QVBoxLayout *dbInfoVContainer = new QVBoxLayout;
    dbInfoVContainer->setContentsMargins(0,0,0,0);
    dbInfoContainer->addLayout(dbInfoVContainer);
    QLabel *infoTitle = new QLabel("MongoDB");
    textStyle("infoTitle", infoTitle, 20, colorWhiteText(), true);
    infoUrl = new QLabel("localhost:2345");
    textStyle("infoUrl", infoUrl, 20, colorTextPrimary(), true);
    dbInfoVContainer->addWidget(infoTitle);
    dbInfoVContainer->addWidget(infoUrl);
    dbInfoContainer->setSpacing(24);
    dbInfoVContainer->setSpacing(0);

    // Кнопки табов
    MenuTabButton *flightTabButton = new MenuTabButton("Данные о перелетах", "flights", "flights_dark", FLIGHTS);
    MenuTabButton *routesTabButton = new MenuTabButton("Данные о маршрутах", "routes", "routes_dark", ROUTES);
    MenuTabButton *mapTabButton = new MenuTabButton("Транспортная сеть", "map", "map_dark", MAP);
    MenuTabButton *analyticsTabButton = new MenuTabButton("Статистика", "analytics", "analytics_dark", ANALYTICS);
    MenuTabButton *settingsTabButton = new MenuTabButton("Настройки", "settings", "settings_dark", SETTINGS);

    menuContainer->addWidget(flightTabButton);
    menuContainer->addWidget(routesTabButton);
    menuContainer->addWidget(mapTabButton);
    menuContainer->addWidget(analyticsTabButton);
    menuContainer->addWidget(settingsTabButton);

    // Контейнер табов ========================================================================
    QFrame *tabsFrame = new QFrame;
    QVBoxLayout *tabsContainer = new QVBoxLayout;
    centerContainer->addWidget(tabsFrame);
    tabsFrame->setLayout(tabsContainer);
    tabsContainer->setContentsMargins(0,0,0,0);
    whiteCardStyle("tabsFrame",tabsFrame);
    tabsFrame->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    coloredCardStyle("MainFragment", this, colorGray(), 0);
    this->setLayout(mainHLayout);
}

MainFragment::~MainFragment() {
    delete infoUrl;
}