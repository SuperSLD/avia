//
// Created by Леонид Соляной on 20.03.2024.
//

#include "AnalyticsTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

AnalyticsTabFragment::AnalyticsTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    mainContainer->setSpacing(0);
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Статистика", "analytics", "analytics_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentContainer->setContentsMargins(0, 0 ,0 ,0);
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    table = new AnalyticTable();
    table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    contentContainer->addWidget(table);

    loadingContainer = new LoadingContainerWidget(contentFrame);
    loadingContainer->startLoading("Загрузка данных");
    mainContainer->addWidget(loadingContainer);
}

AnalyticsTabFragment::~AnalyticsTabFragment() {
    delete loadingContainer;
    delete settingsRep;
    delete dbConnector;
    delete routesFactory;
    delete flightsFactory;
    delete table;
}

void AnalyticsTabFragment::onResume() {

}

void AnalyticsTabFragment::onConnectionChecked(bool isConnected) {
    if (isConnected) {
        if (!analyticsLoaded && !dbConnector->analyticsLoadingInProgress()) {
            loadingContainer->startLoading("Загружаем данные 0%");
            dbConnector->loadAnalytics();
        }
    } else {
        loadingContainer->error("Нет подключения к базе");
    }
}

void AnalyticsTabFragment::setConnector(DBConnector *connector) {
    disconnect(connector, &DBConnector::onConnectionChecked, this, &AnalyticsTabFragment::onConnectionChecked);
    disconnect(connector, &DBConnector::onAnalyticsLoded, this, &AnalyticsTabFragment::onAnalyticsLoaded);
    disconnect(connector, &DBConnector::onChangeAnalyticsLoadedProgress, this,
               &AnalyticsTabFragment::onAnalyticsLoadedChangeProgress);
    this->dbConnector = connector;
    connect(connector, &DBConnector::onAnalyticsLoded, this, &AnalyticsTabFragment::onAnalyticsLoaded);
    connect(connector, &DBConnector::onConnectionChecked, this, &AnalyticsTabFragment::onConnectionChecked);
    connect(connector, &DBConnector::onChangeAnalyticsLoadedProgress, this,
            &AnalyticsTabFragment::onAnalyticsLoadedChangeProgress);
}

void AnalyticsTabFragment::onAnalyticsLoaded(AnalyticsModel analyticsModel) {
    analyticsLoaded = true;
    loadingContainer->stopLoading();
    this->analyticsModel = analyticsModel;
    table->setAnalytics(&analyticsModel);
    qDebug() << "AnalyticsTabFragment::onAnalyticsLoaded" << analyticsModel.allCount << analyticsModel.inRussiaCount;
}

void AnalyticsTabFragment::onAnalyticsLoadedChangeProgress(int progress) {
    if (progress != this->progress) {
        this->progress = progress;
        loadingContainer->startLoading("Загружаем данные " + QString::number(progress) + "%");
    }
}
