//
// Created by Леонид Соляной on 27.04.2024.
//

#include "OSMNetRepository.h"

#include <QVariant>
#include <QJsonArray>

OSMNetRepository::OSMNetRepository(bool debug) {
    service = new ApiService("https://api.openrouteservice.org/v2", this, debug);
}

OSMNetRepository::~OSMNetRepository() { delete service; }

QHash<QString, QString> OSMNetRepository::headers() {
    QHash<QString, QString> headers;
    headers["Authorization"] = "5b3ce3597851110001cf62489146974d2c234021a900b5bff59b9fa5";
    return headers;
}

void OSMNetRepository::direction(double lon1, double lat1, double lon2, double lat2) {
    QJsonObject body;
    QJsonArray p1;
    p1.append(lon1);
    p1.append(lat1);
    QJsonArray p2;
    p2.append(lon2);
    p2.append(lat2);
    QJsonArray coordinates;
    coordinates.append(p1);
    coordinates.append(p2);
    QJsonArray radiuses;
    radiuses.append(5000);
    radiuses.append(5000);
    body["coordinates"] = coordinates;
    body["radiuses"] = radiuses;
    body["maximum_speed"] = 100;

    service->post( "directions/driving-car/json",
        [](QJsonObject o, BaseRep *r) {
            static_cast<OSMNetRepository*>(r)->directionsLoad(OSMDirectionModel(o));
        },
        body
    );
}
