//
// Created by Леонид Соляной on 03.02.2024.
//

#include "MainFragment.h"
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QLabel>
#include <QDebug>

#include <src/ui/common/widgets/menutabbutton/MenuTabButton.h>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

#include "src/ui/fragmentfactory/FragmentFactoryImpl.h"
using namespace screens;

#include "src/ui/screens/main/settingstab/SettingsTabFragment.h"
#include "src/ui/screens/main/flightstab/FlightsTabFragment.h"
#include "src/ui/screens/main/routestab/RoutesTabFragment.h"
#include "src/ui/screens/main/maptab/MapTabFragment.h"
#include "src/ui/screens/main/analyticstab/AnalyticsTabFragment.h"
#include "src/domain/models/tabopen/TabOpenModel.h"

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
    QString ip = settingsRep->getConnectionIp();
    infoUrl->setText(ip.size() > 1 ? ip : "Не выбрано");
    textStyle("infoUrl", infoUrl, 20, colorTextPrimary(), true);
    dbInfoVContainer->addWidget(infoTitle);
    dbInfoVContainer->addWidget(infoUrl);
    dbInfoContainer->setSpacing(24);
    dbInfoVContainer->setSpacing(0);

    // Кнопки табов
    tabButtons.append(new MenuTabButton("Данные о перелетах", "flights", "flights_dark", FLIGHTS));
    tabButtons.append(new MenuTabButton("Данные о маршрутах", "routes", "routes_dark", ROUTES));
    tabButtons.append(new MenuTabButton("Транспортная сеть", "map", "map_dark", MAP));
    tabButtons.append(new MenuTabButton("Статистика", "analytics", "analytics_dark", ANALYTICS));
    tabButtons.append(new MenuTabButton("Настройки", "settings", "settings_dark", SETTINGS));
    foreach(MenuTabButton *button, tabButtons) {
            connect(button, &MenuTabButton::onClicked, this, &MainFragment::onTabButtonClicked);
            menuContainer->addWidget(button);
            button->setSelected(FLIGHTS);
    }

    // Контейнер табов ========================================================================
    QFrame *tabsFrame = new QFrame;
    QVBoxLayout *tabsContainer = new QVBoxLayout;
    centerContainer->addWidget(tabsFrame);
    tabsFrame->setLayout(tabsContainer);
    tabsContainer->setContentsMargins(0,0,0,0);
    whiteCardStyle("tabsFrame",tabsFrame, 0);
    tabsFrame->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    tabs = new QStackedWidget();
    tabs->setContentsMargins(0,0,0,0);
    tabsContainer->addWidget(tabs);

    auto *flightsTabFragment = new FlightsTabFragment();
    connect(flightsTabFragment, &FlightsTabFragment::onModelOpen, this, &MainFragment::onOpenModelDetail);
    tabFragments.append(flightsTabFragment);

    auto *routesTabFragment = new RoutesTabFragment();
    connect(routesTabFragment, &RoutesTabFragment::onModelOpen, this, &MainFragment::onOpenModelDetail);
    tabFragments.append(routesTabFragment);

    tabFragments.append(new MapTabFragment());
    tabFragments.append(new AnalyticsTabFragment());

    auto *settingsTabFragment = new SettingsTabFragment();
    connect(settingsTabFragment, &SettingsTabFragment::onThemeSwitched, this, &MainFragment::onThemeSwitched);
    connect(settingsTabFragment, &SettingsTabFragment::onDatabaseChange, this, &MainFragment::onOpenChangeConnection);
    tabFragments.append(settingsTabFragment);

    foreach(BaseFragment *tab, tabFragments) {
        tabs->addWidget(tab);
    }

    coloredCardStyle("MainFragment", this, colorGray(), 0);
    this->setLayout(mainHLayout);
}

void MainFragment::bindData(BaseModel *model) {
    TabOpenModel tbo = *dynamic_cast<TabOpenModel*>(model);
    tabs->setCurrentIndex(tbo.getTabId());
    foreach(MenuTabButton *button, tabButtons) {
        button->setSelected(tbo.getTabId());
    }
}

MainFragment::~MainFragment() {
    delete infoUrl;
    delete tabs;
    delete settingsRep;
}

void MainFragment::onTabButtonClicked(int id) {
    qDebug() << "MainFragment::onTabButtonClicked ->" << id;
    tabs->setCurrentIndex(id);
    foreach(MenuTabButton *button, tabButtons) {
        button->setSelected(id);
    }
}

void MainFragment::onThemeSwitched() {
    emit provideThemeChanged();
    emit replaceWhithData(MAIN_SCREEN, new TabOpenModel(SETTINGS));
}

void MainFragment::onOpenChangeConnection() {
    emit navigateTo(CHANGE_CONNECTION_SCREEN);
}

void MainFragment::onOpenModelDetail(BaseDBModel *model) {
    emit navigateWhithData(MODEL_DETAIL_SCREEN, model);
}

void MainFragment::onResume() {
    QString ip = settingsRep->getConnectionIp();
    infoUrl->setText(ip.size() > 1 ? ip : "Не выбрано");
    if (connector == nullptr || !connector->dataEquals(settingsRep->getConnectionIp(), settingsRep->getConnectionUser(), settingsRep->setConnectionPassword())) {
        connector = new DBConnector(
                settingsRep->getConnectionIp(),
                settingsRep->getConnectionUser(),
                settingsRep->setConnectionPassword()
        );
    }
    foreach(BaseFragment *tab, tabFragments) {
        tab->setConnector(connector);
        tab->onResume();
    }
    connector->checkConnection();
}

void MainFragment::onPause() {
    foreach(BaseFragment *tab, tabFragments) {
        tab->onPause();
    }
}
