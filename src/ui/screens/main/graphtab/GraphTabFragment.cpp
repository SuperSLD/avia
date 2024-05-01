//
// Created by Леонид Соляной on 21.04.2024.
//

#include "GraphTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"
#include "src/ui/common/widgets/button/Button.h"

GraphTabFragment::GraphTabFragment() {
    auto *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);
    mainContainer->setSpacing(0);

    auto *toolbar = new Toolbar("Расчет графа транспортной сети", "calc", "calc_dark");
    mainContainer->addWidget(toolbar);

    auto *contentFrame = new QFrame();
    auto *contentContainer = new QVBoxLayout();
    contentContainer->setContentsMargins(0, 0, 0, 0);
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    contentContainer->setAlignment(Qt::AlignCenter);

    auto startCalculationButton = new Button("startCalculationButton", "Начать вычисление", true);
    connect(startCalculationButton, &Button::clicked, this, &GraphTabFragment::startCalculation);
    contentContainer->addWidget(startCalculationButton);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);
}

GraphTabFragment::~GraphTabFragment() {
    delete settingsRep;
    delete loadingContainer;
}

void GraphTabFragment::onResume() {

}

void GraphTabFragment::setConnector(DBConnector *connector) {
    disconnect(dbConnector, &DBConnector::onAirportsLoaded, this, &GraphTabFragment::onAirportsLoaded);
    disconnect(dbConnector, &DBConnector::onChangeAirportsLoadedProgress, this, &GraphTabFragment::onAirportsLoadedChangeProgress);
    disconnect(dbConnector, &DBConnector::onGraphCalculated, this, &GraphTabFragment::onGraphCalculated);
    this->dbConnector = connector;
    connect(dbConnector, &DBConnector::onAirportsLoaded, this, &GraphTabFragment::onAirportsLoaded);
    connect(dbConnector, &DBConnector::onChangeAirportsLoadedProgress, this, &GraphTabFragment::onAirportsLoadedChangeProgress);
    connect(dbConnector, &DBConnector::onGraphCalculated, this, &GraphTabFragment::onGraphCalculated);
}

void GraphTabFragment::onConnectionChecked(bool isConnected) {
    if (isConnected) {
        // pass //
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void GraphTabFragment::onAirportsLoaded(TransportGraphModel graph, bool fromDB) {
    if (fromDB) {
        loadingContainer->stopLoading();
        this->graph = graph;
    }
}

void GraphTabFragment::onAirportsLoadedChangeProgress(int progress) {
    loadingContainer->startLoading("Поиск аэропортов " + QString::number(progress) + "%");
}

void GraphTabFragment::startCalculation() {
    dbConnector->calculateGraph(graph);
    loadingContainer->startLoading("Считаем");
}

void GraphTabFragment::onGraphCalculated() {
    loadingContainer->stopLoading();
}

