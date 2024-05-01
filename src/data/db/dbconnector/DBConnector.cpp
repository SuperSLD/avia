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

void DBConnector::handleAirportsLoaded(TransportGraphModel graph) {
    getAirportsWorkerIsStart = false;
    emit onAirportsLoaded(graph);
}

void DBConnector::handleAirportsLoadedProgress(int progress) {
    emit onChangeAirportsLoadedProgress(progress);
}

void DBConnector::calculateArea(TransportGraphModel graph, OSMNetRepository *netRep) {
    if (calculateAreaWorker != nullptr) calculateAreaWorker->exit();
    calculateAreaWorker = new CalculateAreaWorker("mongodb://" + user + ":" + password + "@" + url, graph);
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

void DBConnector::calculateGraph(TransportGraphModel graph) {
    if (calculateGraphWorker != nullptr) calculateGraphWorker->exit();
    calculateGraphWorker = new CalculateGraphWorker("mongodb://" + user + ":" + password + "@" + url, graph);
    connect(calculateGraphWorker, &CalculateGraphWorker::resultReady, this, &DBConnector::handleCalculatedGraph);
    calculateGraphWorker->start();
}

void DBConnector::handleCalculatedGraph() {
    emit onGraphCalculated();
}
