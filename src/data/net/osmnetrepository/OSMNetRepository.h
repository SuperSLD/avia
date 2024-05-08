//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_OSMNETREPOSITORY_H
#define AVIA_OSMNETREPOSITORY_H


#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QList>
#include <QNetworkReply>
#include <QUuid>
#include "src/data/net/apiservice/ApiService.h"
#include "src/data/net/models/datawrapper/DataWrapper.h"
#include "src/data/net/models/osm/direcrion/OSMDirectionModel.h"

class OSMNetRepository: public QObject, BaseRep {
        Q_OBJECT

private:
    ApiService *service;

public:
    OSMNetRepository(bool debug = false);
    ~OSMNetRepository();

    QHash<QString, QString> headers() override;

    void direction(double lon1, double lat1, double lon2, double lat2);

signals:
    void directionsLoad(OSMDirectionModel direction);
};


#endif //AVIA_OSMNETREPOSITORY_H
