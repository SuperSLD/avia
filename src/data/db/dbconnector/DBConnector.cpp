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
    if (getAnalyticsWorker != nullptr) getAnalyticsWorker->exit();
    getAnalyticsWorker = new GetAnalyticsWorker("mongodb://" + user + ":" + password + "@" +url);
    connect(getAnalyticsWorker, &GetAnalyticsWorker::resultReady, this, &DBConnector::handleAnalyticsLoaded);
    connect(getAnalyticsWorker, &GetAnalyticsWorker::onChangeProgress, this, &DBConnector::handleAnalyticsLoadedProgress);
    getAnalyticsWorker->start();
}

void DBConnector::handleAnalyticsLoaded(AnalyticsModel analyticsModel) {
    emit onAnalyticsLoded(analyticsModel);
}

void DBConnector::handleAnalyticsLoadedProgress(int progress) {
    emit onChangeAnalyticsLoadedProgress(progress);
}

bool DBConnector::analyticsLoadingInProgress() {
    return getAnalyticsWorker != nullptr && getAnalyticsWorker->isRunning();
}