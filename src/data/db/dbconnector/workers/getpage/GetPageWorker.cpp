//
// Created by Леонид Соляной on 07.04.2024.
//

#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include "GetPageWorker.h"
#include <QString>
#include <QJsonArray>
#include <bsoncxx/json.hpp>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include <mongocxx/options/find.hpp>
#include <mongocxx/options/find-fwd.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

void GetPageWorker::run() {
    QJsonArray result = QJsonArray();
    try {
        mongocxx::uri uri((uriString.toStdString()));
        mongocxx::client client(uri);
        auto cursor_all = client["avianav"][table.toStdString()].find(
                {},mongocxx::options::find{}.skip(pageSize*page).limit(pageSize)
        );
        for (auto doc : cursor_all) {
            auto document = QJsonDocument::fromJson(
                    QByteArray::fromStdString(
                            bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed)
                    )
            );
            result.push_back(document.object());
        }
        emit resultReady(result, table);
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(result, table);
    }
}