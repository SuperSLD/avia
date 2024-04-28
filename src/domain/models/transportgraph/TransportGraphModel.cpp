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
    return {emptyEdgesList};
}

AirportModel TransportGraphModel::getMinDistanceAirport(double lon, double lat) {
    double minDistance = 100000000000.0;
    AirportModel minDistanceAirport;
    foreach(auto airport, airports) {
        auto distance = sqrt(pow(lat - airport.lat, 2) + pow(lon - airport.lon, 2));
        if (distance < minDistance) {
            minDistance = distance;
            minDistanceAirport = airport;
        }
    }
    return minDistanceAirport;
}
