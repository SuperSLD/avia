//
// Created by Леонид Соляной on 10.04.2024.
//

#include "GetAnalyticsWorker.h"

#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
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

void GetAnalyticsWorker::run() {
    QList<FlightModel*> result;
    //QJsonArray result = QJsonArray();
    try {
        mongocxx::uri uri((uriString.toStdString()));
        mongocxx::client client(uri);
        auto cursor_all = client["avianav"][factory->tableName().toStdString()].find({});
        auto count = client["avianav"][factory->tableName().toStdString()].count_documents({});
        double index = 0;
        for (auto doc : cursor_all) {
            auto document = QJsonDocument::fromJson(
                    QByteArray::fromStdString(
                            bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed)
                    )
            );
            result.append(dynamic_cast<FlightModel*>(factory->createModel(document.object())));
            index++;
            emit onChangeProgress(index / count * 100);
        }
        emit resultReady(AnalyticsModel(result));
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(AnalyticsModel(result));
    }
}
