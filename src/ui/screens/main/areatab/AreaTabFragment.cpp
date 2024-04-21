//
// Created by Леонид Соляной on 21.04.2024.
//

#include "AreaTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

AreaTabFragment::AreaTabFragment() {
    auto *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);
    mainContainer->setSpacing(0);

    auto *toolbar = new Toolbar("Рассчет транспортной доступности", "map", "map_dark");
    mainContainer->addWidget(toolbar);

    auto *contentFrame = new QFrame();
    auto *contentContainer = new QVBoxLayout();
    contentContainer->setContentsMargins(0, 0, 0, 0);
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);



    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);
}

AreaTabFragment::~AreaTabFragment() {
    delete settingsRep;
    delete loadingContainer;
}

void AreaTabFragment::onResume() {

}

void AreaTabFragment::setConnector(DBConnector *connector) {
    disconnect(dbConnector, &DBConnector::onAirportsLoaded, this, &AreaTabFragment::onAirportsLoaded);
    disconnect(dbConnector, &DBConnector::onChangeAirportsLoadedProgress, this, &AreaTabFragment::onAirportsLoadedChangeProgress);
    this->dbConnector = connector;
    connect(dbConnector, &DBConnector::onAirportsLoaded, this, &AreaTabFragment::onAirportsLoaded);
    connect(dbConnector, &DBConnector::onChangeAirportsLoadedProgress, this, &AreaTabFragment::onAirportsLoadedChangeProgress);
}

void AreaTabFragment::onConnectionChecked(bool isConnected) {
    if (isConnected) {
        // pass //
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void AreaTabFragment::onAirportsLoaded(QList<AirportModel> airports) {
    loadingContainer->stopLoading();
}

void AreaTabFragment::onAirportsLoadedChangeProgress(int progress) {
    loadingContainer->startLoading("Поиск аэропортов " + QString::number(progress) + "%");
}
