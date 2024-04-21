//
// Created by Леонид Соляной on 16.04.2024.
//

#include "GetAllRoutesWorker.h"

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

void GetAllRoutesWorker::run() {
    QList<RouteModel*> result;
    QList<QString> addedRoute;
    try {
        mongocxx::uri uri((uriString.toStdString()));
        mongocxx::client client(uri);
        auto cursor_all = client["avianav"][factory->tableName().toStdString()].find(
                {}, mongocxx::options::find{}.limit(LOADING_LIMIT));
        //auto count = client["avianav"][factory->tableName().toStdString()].count_documents({});
        auto count = LOADING_LIMIT;
        double index = 0;
        for (auto doc : cursor_all) {
            auto document = QJsonDocument::fromJson(
                    QByteArray::fromStdString(
                            bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed)
                    )
            );
            auto route = dynamic_cast<RouteModel*>(factory->createModel(document.object()));
            auto routeCode = route->data.current.apdstia + route->data.current.aporgci;
            auto routeCodeRev = route->data.current.aporgci + route->data.current.apdstia;
            if (!addedRoute.contains(routeCode) && !addedRoute.contains(routeCodeRev) && route->data.current.inRussia()) {
                result.append(route);
                addedRoute.append(routeCode);
                addedRoute.append(routeCodeRev);
            }
            index++;
            emit onChangeProgress(index / count * 100);
        }
        emit resultReady(result);
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(result);
    }
}