//
// Created by Леонид Соляной on 20.03.2024.
//

#include "RoutesTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

RoutesTabFragment::RoutesTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Данные о маршрутах", "routes", "routes_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);}

RoutesTabFragment::~RoutesTabFragment() {
    delete loadingContainer;
    delete settingsRep;
    delete dbConnector;
}

void RoutesTabFragment::onResume() {

}

void RoutesTabFragment::onConnectionChecked(bool isConnected) {
    if (isConnected) {
        loadingContainer->stopLoading();
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void RoutesTabFragment::setConnector(DBConnector *connector) {
    disconnect(connector, &DBConnector::onConnectionChecked, this, &RoutesTabFragment::onConnectionChecked);
    this->dbConnector = connector;
    connect(connector, &DBConnector::onConnectionChecked, this, &RoutesTabFragment::onConnectionChecked);
}

