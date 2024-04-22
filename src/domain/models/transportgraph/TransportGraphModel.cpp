//
// Created by Леонид Соляной on 22.04.2024.
//

#include "TransportGraphModel.h"

TransportGraphModel::TransportGraphModel(QList<AirportModel> airports) {
    this->airports = airports;
}

TransportGraphModel TransportGraphModel::getWithEmptyEdges() {
    QList<AirportModel> emptyEdgesList;
    foreach(auto airport, airports) {
        emptyEdgesList.append(airport.getWithEmptyEdges());
    }
    return TransportGraphModel(emptyEdgesList);
}
