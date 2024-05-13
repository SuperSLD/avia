//
// Created by Леонид Соляной on 31.03.2024.
//

#include "DBConnector.h"
#include "src/data/db/dbconnector/workers/checkconnection/CheckConnectionWorker.h"
#include "src/data/db/dbconnector/workers/getpage/GetPageWorker.h"
#include <QString>
#include <QList>
#include <QDebug>
#include <thread>
#include <QJsonArray>

DBConnector::DBConnector(QString url, QString user, QString password) {
    this->url = url;
    this->user = user;
    this->password = password;
    qDebug() << "DBConnector invoke constructor" << url << user << password.size();
}

DBConnector::~DBConnector() {
    if (checkConnectionWorker != nullptr) {
        checkConnectionWorker->exit();
        delete checkConnectionWorker;
    }
    if (getPageWorker != nullptr) {
        getPageWorker->exit();
        delete getPageWorker;
    }
    if (getAnalyticsWorker != nullptr) {
        getAnalyticsWorker->exit();
        delete getAnalyticsWorker;
    }
    if (getAllRoutesWorker != nullptr) {
        getAllRoutesWorker->exit();
        delete getAllRoutesWorker;
    }
    if (getAirportsWorker != nullptr) {
        getAirportsWorker->exit();
        delete getAirportsWorker;
    }
}

bool DBConnector::dataEquals(QString url, QString user, QString password) {
    return url == this->url && user == this->user && password == this->password;
}

void DBConnector::checkConnection() {
    if (checkConnectionWorker != nullptr) checkConnectionWorker->exit();
    checkConnectionWorker = new CheckConnectionWorker("mongodb://" + user + ":" + password + "@" + url);
    connect(checkConnectionWorker, &CheckConnectionWorker::resultReady, this, &DBConnector::handleConnectionChecked);
    checkConnectionWorker->start();
}

void DBConnector::handleConnectionChecked(bool isConnected) {
    qDebug() << "DBConnector::handleConnectionChecked" << isConnected;
    emit onConnectionChecked(isConnected);
}

void DBConnector::loadPage(QString table, int page, int pageSize) {
    if (getPageWorker != nullptr) getPageWorker->exit();
    getPageWorker = new GetPageWorker("mongodb://" + user + ":" + password + "@" +url, table, page, pageSize);
    connect(getPageWorker, &GetPageWorker::resultReady, this, &DBConnector::handleLoadedPage);
    getPageWorker->start();
}

void DBConnector::handleLoadedPage(QJsonArray array, QString table) {
    qDebug() << "DBConnector::handleLoadedPage" << array.size();
    emit onPageLoaded(array, table);
}

void DBConnector::loadAnalytics() {
    if (!getAnalyticsWorkerIsStart) {
        getAnalyticsWorkerIsStart = true;
        if (getAnalyticsWorker != nullptr) getAnalyticsWorker->exit();
        getAnalyticsWorker = new GetAnalyticsWorker("mongodb://" + user + ":" + password + "@" + url);
        connect(getAnalyticsWorker, &GetAnalyticsWorker::resultReady, this, &DBConnector::handleAnalyticsLoaded);
        connect(getAnalyticsWorker, &GetAnalyticsWorker::onChangeProgress, this,
                &DBConnector::handleAnalyticsLoadedProgress);
        getAnalyticsWorker->start();
    }
}

void DBConnector::handleAnalyticsLoaded(AnalyticsModel analyticsModel) {
    getAnalyticsWorkerIsStart = false;
    emit onAnalyticsLoded(analyticsModel);
}

void DBConnector::handleAnalyticsLoadedProgress(int progress) {
    emit onChangeAnalyticsLoadedProgress(progress);
}

bool DBConnector::analyticsLoadingInProgress() {
    return getAnalyticsWorker != nullptr && getAnalyticsWorker->isRunning();
}

void DBConnector::loadRoutes() {
    if (!getAllRoutesWorkerIsStart) {
        getAllRoutesWorkerIsStart = true;
        if (getAllRoutesWorker != nullptr) getAllRoutesWorker->exit();
        getAllRoutesWorker = new GetAllRoutesWorker("mongodb://" + user + ":" + password + "@" + url);
        connect(getAllRoutesWorker, &GetAllRoutesWorker::resultReady, this, &DBConnector::handleRoutesLoaded);
        connect(getAllRoutesWorker, &GetAllRoutesWorker::onChangeProgress, this,
                &DBConnector::handleAllRoutesLoadedProgress);
        getAllRoutesWorker->start();
    }
}

bool DBConnector::routesLoadingInProgress() {
    return getAllRoutesWorker != nullptr && getAllRoutesWorker->isRunning();
}

void DBConnector::handleRoutesLoaded(QList<RouteModel*> routes) {
    getAllRoutesWorkerIsStart = false;
    emit onRoutesLoaded(routes);
}

void DBConnector::handleAllRoutesLoadedProgress(int progress) {
    emit onChangeRoutesLoadedProgress(progress);
}

void DBConnector::loadAirports() {
    if (!getAirportsWorkerIsStart) {
        getAirportsWorkerIsStart = true;
        if (getAirportsWorker != nullptr) getAirportsWorker->exit();
        getAirportsWorker = new GetAirportsWorker("mongodb://" + user + ":" + password + "@" + url);
        connect(getAirportsWorker, &GetAirportsWorker::resultReady, this, &DBConnector::handleAirportsLoaded);
        connect(getAirportsWorker, &GetAirportsWorker::onChangeProgress, this,
                &DBConnector::handleAirportsLoadedProgress);
        getAirportsWorker->start();
    }
}

void DBConnector::handleAirportsLoaded(TransportGraphModel graph, bool fromDB) {
    getAirportsWorkerIsStart = false;
    emit onAirportsLoaded(graph, fromDB);
}

void DBConnector::handleAirportsLoadedProgress(int progress) {
    emit onChangeAirportsLoadedProgress(progress);
}

void DBConnector::calculateArea(TransportGraphModel graph, OSMNetRepository *netRep, double diff) {
    if (calculateAreaWorker != nullptr) calculateAreaWorker->exit();
    calculateAreaWorker = new CalculateAreaWorker("mongodb://" + user + ":" + password + "@" + url, graph, diff);
    connect(calculateAreaWorker, &CalculateAreaWorker::resultReady, this, &DBConnector::handleCalculatedArea);
    connect(calculateAreaWorker, &CalculateAreaWorker::onChangeProgress, this, &DBConnector::handleCalculatedAreaProgress);
    connect(calculateAreaWorker, &CalculateAreaWorker::direction, netRep, &OSMNetRepository::direction);
    connect(netRep, &OSMNetRepository::directionsLoad, calculateAreaWorker, &CalculateAreaWorker::directionLoad);
    calculateAreaWorker->start();
}

void DBConnector::handleCalculatedAreaProgress(int progress) {
    emit onChangeCalculateAreaProgress(progress);
}

void DBConnector::handleCalculatedArea(Area area) {
    emit onAreaCalculated(area);
}

void DBConnector::calculateGraph(TransportGraphModel graph, QString key, double greed, double gregariousness, double passengersPart) {
    if (calculateGraphWorker != nullptr) calculateGraphWorker->exit();
    calculateGraphWorker = new CalculateGraphWorker(key, graph, greed, gregariousness, passengersPart);
    connect(calculateGraphWorker, &CalculateGraphWorker::resultReady, this, &DBConnector::handleCalculatedGraph);
    connect(calculateGraphWorker, &CalculateGraphWorker::onChangeProgress, this, &DBConnector::handleCalculatedGraphProgress);
    calculateGraphWorker->start();
}

void DBConnector::handleCalculatedGraph(QString key, TransportGraphModel graph) {
    emit onGraphCalculated(key, graph);
}

void DBConnector::handleCalculatedGraphProgress(int progress) {
    emit onChangeCalculateGraphProgress(progress);
}

void DBConnector::loadSavedData() {
    if (loadSavedDataWorker != nullptr) loadSavedDataWorker->exit();
    loadSavedDataWorker = new LoadSavedDataWorker();
    connect(loadSavedDataWorker, &LoadSavedDataWorker::areaLolad, this, &DBConnector::handleCalculatedArea);
    connect(loadSavedDataWorker, &LoadSavedDataWorker::airportsLolad, this, &DBConnector::handleAirportsLoaded);
    connect(loadSavedDataWorker, &LoadSavedDataWorker::graphLoad, this, &DBConnector::handleCalculatedGraph);
    loadSavedDataWorker->start();
}

void DBConnector::startMetricsCalculation() {
    if (calcMetricsWorker != nullptr) calcMetricsWorker->exit();
    calcMetricsWorker = new CalcMetricsWorker();
    connect(this, &DBConnector::onAirportsLoaded, calcMetricsWorker, &CalcMetricsWorker::airportsLoad);
    connect(this, &DBConnector::onGraphCalculated, calcMetricsWorker, &CalcMetricsWorker::onGraphLoaded);
    connect(this, &DBConnector::onAreaCalculated, calcMetricsWorker, &CalcMetricsWorker::areaLoad);
    connect(calcMetricsWorker, &CalcMetricsWorker::metricsUpdated, this, &DBConnector::handleMetricsUpdated);
    calcMetricsWorker->start();
}

void DBConnector::handleMetricsUpdated(MetricsModel metrics) {
    emit metricsUpdated(metrics);
}

void DBConnector::stopMetricsCalculation() {
    qDebug() << "DBConnector::stopMetricsCalculation";
    if (calcMetricsWorker != nullptr) {
        qDebug() << "DBConnector::stopMetricsCalculation" << "calcMetricsWorker != nullptr";
        calcMetricsWorker->disable();
        calcMetricsWorker->exit();
    }
}

