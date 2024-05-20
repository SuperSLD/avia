//
// Created by Леонид Соляной on 21.04.2024.
//

#include "GetAirportsWorker.h"
#include "src/data/db/dbconnector/models/flightmodel/FlightModel.h"
#include "src/domain/models/transportgraph/aircraftmodels/AircraftModelsBlock.h"

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

#include "src/domain/usecases/math/math_functions.h"
using namespace math_functions;

void GetAirportsWorker::run() {
    auto passengersCount = AircraftModelsBlock();
    auto aircraftHash = QHash<QString, int>();
    try {
        mongocxx::uri uri((uriString.toStdString()));
        mongocxx::client client(uri);
        auto cursor_all = client["avianav"][factory->tableName().toStdString()].find({});
        auto count = client["avianav"][factory->tableName().toStdString()].count_documents({});
        double index = 0;
        auto sumCost = 0;
        for (auto doc : cursor_all) {
            auto document = QJsonDocument::fromJson(
                    QByteArray::fromStdString(
                            bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed)
                    )
            );
            auto flight = dynamic_cast<FlightModel*>(factory->createModel(document.object()));
            if (flight->data.inRussia()) {
                auto aircraftModel = flight->data.act;
                auto aircraft = passengersCount.getByModel(aircraftModel);
                if (aircraftHash.contains(aircraftModel)) {
                    aircraftHash[aircraftModel] += 1;
                } else {
                    aircraftHash[aircraftModel] = 1;
                }
                auto passCount = passengersCount.passengersCount(0.8, aircraftModel);
                auto distance = distanceInKm(
                        flight->data.apdstlo,flight->data.apdstla,
                        flight->data.aporglo, flight->data.aporgla
                );
                sumCost += distance * aircraft.kilometerCost;
                auto airport = AirportModel(
                        flight->data.apdstia,
                        flight->data.apdstna,
                        flight->data.apdstci,
                        flight->data.apdstlo,
                        flight->data.apdstla,
                        passCount,
                        0,
                        QList<QString>()
                );
                if (airports.contains(airport.id)) {
                    if (flight->data.aporgia.size() > 1) {
                        airports[airport.id].incFlight();
                        airports[airport.id].addConnection(flight->data.aporgia);
                        auto pCount = passCount;
                        if (airports.contains(flight->data.aporgia)) {
                            airports[flight->data.aporgia].incPassengerCount(pCount, true, flight->data.aporgia);
                        }
                        airports[airport.id].incPassengerCount(pCount,false, flight->data.aporgia);
                    }
                } else {
                    airports[airport.id] = airport;
                }
            }
            index++;
            emit onChangeProgress(index / count * 100);
        }

        auto graph = TransportGraphModel(airports.values(), "s0", 0.0, 0.0, sumCost, 1.0);
        graph.setAircraftCount(aircraftHash);
        settingsRepository->setJson("airports", graph.toJson());
        emit resultReady(graph, true);
    } catch (std::exception& e) {
        qDebug("%s", e.what());
        emit resultReady(TransportGraphModel(airports.values()), true);
    }
}