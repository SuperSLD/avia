//
// Created by Леонид Соляной on 31.03.2024.
//

#include "DBConnector.h"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

DBConnector::DBConnector(QString url, QString user, QString password) {
    mongocxx::instance instance{};
    mongocxx::uri uri(("mongodb://" + user + ":" + password + "@" +url).toStdString());
    mongocxx::client client(uri);
    auto db = client["avianav"];
}

DBConnector::~DBConnector() {

}
