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
        emit resultReady(!client.list_database_names().empty());
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(false);
    }
}

