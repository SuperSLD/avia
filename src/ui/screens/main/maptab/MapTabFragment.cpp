//
// Created by Леонид Соляной on 20.03.2024.
//

#include "MapTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

MapTabFragment::MapTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);
    mainContainer->setSpacing(0);

    Toolbar *toolbar = new Toolbar("Транспортная сеть", "map", "map_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentContainer->setContentsMargins(0, 0, 0, 0);
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    map = new MapWidget();
    map->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    contentContainer->addWidget(map);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);
}

MapTabFragment::~MapTabFragment() {
    delete loadingContainer;
    delete settingsRep;
    delete dbConnector;
}

void MapTabFragment::onResume() {

}

void MapTabFragment::onConnectionChecked(bool isConnected) {
    if (isConnected) {
        loadingContainer->stopLoading();
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void MapTabFragment::setConnector(DBConnector *connector) {
    disconnect(connector, &DBConnector::onAirportsLoaded, this, &MapTabFragment::onAirportsLoaded);
    disconnect(connector, &DBConnector::onConnectionChecked, this, &MapTabFragment::onConnectionChecked);
    this->dbConnector = connector;
    connect(connector, &DBConnector::onConnectionChecked, this, &MapTabFragment::onConnectionChecked);
    connect(connector, &DBConnector::onAirportsLoaded, this, &MapTabFragment::onAirportsLoaded);
}

void MapTabFragment::onAirportsLoaded(TransportGraphModel graph) {
    loadingContainer->stopLoading();
    map->setAirports(graph);
}


