//
// Created by Леонид Соляной on 04.04.2024.
//
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include "CheckConnectionWorker.h"
#include <QDebug>

void CheckConnectionWorker::run() {
    try {
        mongocxx::uri uri((uriString.toStdString()));
        mongocxx::client client(uri);
        qDebug() << "DBConnector check connection";
                foreach(std::string name, client["avianav"].list_collection_names()) {
                qDebug() << "DBConnector ->" << QString::fromStdString(name);
            }
        emit resultReady(!client.list_database_names().empty());
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(false);
    }
}

