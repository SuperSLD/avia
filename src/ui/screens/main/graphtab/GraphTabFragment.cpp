//
// Created by Леонид Соляной on 21.04.2024.
//

#include "GraphTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"
#include "src/ui/common/widgets/button/Button.h"
#include "src/ui/common/widgets/switcher/Switcher.h"
#include "src/domain/models/transportgraph/PriorityQueue.h"

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
    contentContainer->setSpacing(0);
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    contentContainer->setAlignment(Qt::AlignCenter);

    table = new AnalyticTable();
    table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    contentContainer->addWidget(table);

    auto *buttonContainer = new QHBoxLayout;
    buttonContainer->setAlignment(Qt::AlignRight);
    buttonContainer->setContentsMargins(24, 24, 24, 24);
    buttonContainer->setSpacing(16);

    passengersPartEdit = new TextEdit("passengersPartEdit", "Часть пассажиров");
    passengersPartEdit->setMaximumWidth(650);
    passengersPartEdit->setText("0.001");
    buttonContainer->addWidget(passengersPartEdit);

    greedEdit = new TextEdit("greedEdit", "Жадность");
    greedEdit->setMaximumWidth(650);
    buttonContainer->addWidget(greedEdit);

    gregariousnessEdit = new TextEdit("gregariousnessEdit", "Стадность");
    gregariousnessEdit->setMaximumWidth(650);
    buttonContainer->addWidget(gregariousnessEdit);

    QList<QString> saves = QList<QString>();
    saves.append("s1");
    saves.append("s2");
    saves.append("s3");
    saves.append("s4");
    Switcher *saveSwitcher = new Switcher("themeSwitcher", saves, save);
    connect(saveSwitcher, &Switcher::onVariantSwitched, this, &GraphTabFragment::onSaveSelected);
    saveSwitcher->setMinimumWidth(200);
    buttonContainer->addWidget(saveSwitcher);

    auto startCalculationButton = new Button("startCalculationButton", "Начать вычисление", true);
    connect(startCalculationButton, &Button::clicked, this, &GraphTabFragment::startCalculation);
    buttonContainer->addWidget(startCalculationButton);
    contentContainer->addLayout(buttonContainer);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Проверка подключения");
    mainContainer->addWidget(loadingContainer);
}

GraphTabFragment::~GraphTabFragment() {
    delete settingsRep;
    delete loadingContainer;
    delete table;
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
    connect(dbConnector, &DBConnector::onChangeCalculateGraphProgress, this, &GraphTabFragment::onCalculateGraphProgressChange);
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
        graphLoaded = true;
        this->graph = graph;
    }
}

void GraphTabFragment::onAirportsLoadedChangeProgress(int progress) {
    loadingContainer->startLoading("Поиск аэропортов " + QString::number(progress) + "%");
}

void GraphTabFragment::startCalculation() {
    dbConnector->calculateGraph(
            graph,
            save,
            greedEdit->text().toDouble(),
            gregariousnessEdit->text().toDouble(),
            passengersPartEdit->text().toDouble()
    );
    loadingContainer->startLoading("Считаем");
}

void GraphTabFragment::onGraphCalculated(QString key, TransportGraphModel graph) {
    if (graphLoaded) loadingContainer->stopLoading();
    results[key] = TransportGraphModel(graph);
    onSaveSelected(save);
}

void GraphTabFragment::onCalculateGraphProgressChange(int progress) {
    loadingContainer->startLoading(save + " -> Нераспределенные пассажиры " + QString::number(progress));
}

void GraphTabFragment::onSaveSelected(QString save) {
    this->save = save;
    if (results.contains(save)) {
        table->setAnalytics(&results[save]);
    } else {
        table->setAnalytics(new TransportGraphModel());
    }
}

