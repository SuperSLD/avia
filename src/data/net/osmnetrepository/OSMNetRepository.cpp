//
// Created by Леонид Соляной on 27.04.2024.
//

#include "OSMNetRepository.h"

#include <QVariant>

OSMNetRepository::OSMNetRepository(bool debug) {
    service = new ApiService("https://api.openstreetmap.org", this, debug);
}

OSMNetRepository::~OSMNetRepository() { delete service; }

QHash<QString, QString> OSMNetRepository::headers() {
    QHash<QString, QString> headers;
    return headers;
}

void OSMNetRepository::getVersions() {
    service->get( "api/versions.json",
        [](QJsonObject o, BaseRep *r) {
            static_cast<OSMNetRepository*>(r)->versionsLoad(OSMVersionsModel(o));
        }
    );
}
