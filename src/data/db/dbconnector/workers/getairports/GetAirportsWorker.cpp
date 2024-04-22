//
// Created by Леонид Соляной on 21.04.2024.
//

#include "GetAirportsWorker.h"
#include "src/data/db/dbconnector/models/flightmodel/FlightModel.h"

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

void GetAirportsWorker::run() {
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
            auto flight = dynamic_cast<FlightModel*>(factory->createModel(document.object()));
            if (flight->data.inRussia()) {
                auto airport = AirportModel(
                        flight->data.apdstia,
                        flight->data.apdstna,
                        flight->data.apdstci,
                        flight->data.apdstlo,
                        flight->data.apdstla,
                        QList<QString>()
                );
                if (airports.contains(airport.id)) {
                    if (flight->data.aporgia.size() > 1) {
                        airports[airport.id].incFlight();
                        airports[airport.id].addConnection(flight->data.aporgia);
                    }
                } else {
                    airports[airport.id] = airport;
                }
            }
            index++;
            emit onChangeProgress(index / count * 100);
        }
        emit resultReady(TransportGraphModel(airports.values()));
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(TransportGraphModel(airports.values()));
    }
}