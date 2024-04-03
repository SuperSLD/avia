//
// Created by Леонид Соляной on 31.03.2024.
//

#include "DBConnector.h"

#include <QDebug>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>

DBConnector::DBConnector(QString url, QString user, QString password) {
    this->url = url;
    this->user = user;
    this->password = password;
}

DBConnector::~DBConnector() {

}

bool DBConnector::isConnected() {
    try {
        mongocxx::uri uri(("mongodb://" + user + ":" + password + "@" +url).toStdString());
        mongocxx::client client(uri);
        qDebug() << "DBConnector check connection";
                foreach(std::string name, client["avianav"].list_collection_names()) {
                qDebug() << "DBConnector ->" << QString::fromStdString(name);
            }
        return !client.list_database_names().empty();
    } catch (std::exception& e) {
        qDebug("%s", e.what());
    }
    return false;
}
