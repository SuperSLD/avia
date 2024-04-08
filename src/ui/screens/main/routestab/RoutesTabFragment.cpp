//
// Created by Леонид Соляной on 20.03.2024.
//

#include "RoutesTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"
#include "src/data/db/dbconnector/modelfactory/routesmodelfactory/RoutesModelFactory.h"

RoutesTabFragment::RoutesTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    mainContainer->setSpacing(0);
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0, 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Данные о перелетах", "flights", "flights_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentContainer->setContentsMargins(0, 0, 0, 0);
    contentFrame->setLayout(contentContainer);

    table = new Table(new RoutesModelFactory);
    table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    contentContainer->addWidget(table);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);
}

RoutesTabFragment::~RoutesTabFragment() {
        delete loadingContainer;
        delete settingsRep;
        delete dbConnector;
        delete table;
}

void RoutesTabFragment::onResume() {

}

void RoutesTabFragment::onConnectionChecked(bool isConnected) {
    if (isConnected) {
        loadingContainer->stopLoading();
        table->setConnector(dbConnector);
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void RoutesTabFragment::setConnector(DBConnector *connector) {
    disconnect(connector, &DBConnector::onConnectionChecked, this, &RoutesTabFragment::onConnectionChecked);
    this->dbConnector = connector;
    connect(connector, &DBConnector::onConnectionChecked, this, &RoutesTabFragment::onConnectionChecked);
}

