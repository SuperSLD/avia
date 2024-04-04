//
// Created by Леонид Соляной on 31.03.2024.
//

#include "DBConnector.h"
#include "src/data/db/dbconnector/workers/checkconnection/CheckConnectionWorker.h"

#include <QDebug>
#include <thread>

DBConnector::DBConnector(QString url, QString user, QString password) {
    this->url = url;
    this->user = user;
    this->password = password;
}

DBConnector::~DBConnector() {

}

void DBConnector::checkConnection() {
    auto *checkConnection = new CheckConnectionWorker("mongodb://" + user + ":" + password + "@" +url);
    connect(checkConnection, &CheckConnectionWorker::resultReady, this, &DBConnector::handleConnectionChecked);
    checkConnection->start();
}

void DBConnector::handleConnectionChecked(bool isConnected) {
    emit onConnectionChecked(isConnected);
}
