//
// Created by Леонид Соляной on 18.03.2024.
//

#include "FlightsTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"
#include "src/data/db/dbconnector/modelfactory/flightmodelsfactory/FlightModelsFactory.h"

FlightsTabFragment::FlightsTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    mainContainer->setSpacing(0);
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Данные о перелетах", "flights", "flights_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentContainer->setContentsMargins(0, 0 ,0 ,0);
    contentFrame->setLayout(contentContainer);

    table = new Table(new FlightModelsFactory);
    connect(table, &Table::onModelOpen, this, &FlightsTabFragment::handleModelOpen);
    table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    contentContainer->addWidget(table);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);
}

FlightsTabFragment::~FlightsTabFragment() {
    delete loadingContainer;
    delete settingsRep;
    delete dbConnector;
    delete table;
}

void FlightsTabFragment::onResume() {

}

void FlightsTabFragment::onConnectionChecked(bool isConnected) {
    qDebug() << "FlightsTabFragment::onConnectionChecked";
    if (isConnected) {
        loadingContainer->stopLoading();
        table->setConnector(dbConnector);
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void FlightsTabFragment::setConnector(DBConnector *connector) {
    disconnect(connector, &DBConnector::onConnectionChecked, this, &FlightsTabFragment::onConnectionChecked);
    this->dbConnector = connector;
    connect(connector, &DBConnector::onConnectionChecked, this, &FlightsTabFragment::onConnectionChecked);
}

void FlightsTabFragment::handleModelOpen(BaseDBModel *model) {
    emit onModelOpen(model);
}
