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
    disconnect(connector, &DBConnector::onAreaCalculated, this, &MapTabFragment::onAreaCalculated);
    disconnect(connector, &DBConnector::onGraphCalculated, this, &MapTabFragment::onGraphCalculated);
    this->dbConnector = connector;
    connect(connector, &DBConnector::onConnectionChecked, this, &MapTabFragment::onConnectionChecked);
    connect(connector, &DBConnector::onAirportsLoaded, this, &MapTabFragment::onAirportsLoaded);
    connect(connector, &DBConnector::onAreaCalculated, this, &MapTabFragment::onAreaCalculated);
    connect(connector, &DBConnector::onGraphCalculated, this, &MapTabFragment::onGraphCalculated);
}

void MapTabFragment::onAirportsLoaded(TransportGraphModel graph, bool fromDB) {
    loadingContainer->stopLoading();
    map->setGraph(graph);
}

void MapTabFragment::onAreaCalculated(Area area) {
    map->setArea(area);
}

void MapTabFragment::onGraphCalculated(QString key, TransportGraphModel graph) {
    map->setGraph(graph, key);
}
