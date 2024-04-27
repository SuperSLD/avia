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
#include "src/data/net/models/osm/versions/OSMVersionsModel.h"
#include "src/data/net/models/datawrapper/DataWrapper.h"

class OSMNetRepository: public QObject, BaseRep {
        Q_OBJECT

private:
    ApiService *service;

public:
    //https://api.openstreetmap.org/api/versions.json
    OSMNetRepository(bool debug = false);
    ~OSMNetRepository();

    QHash<QString, QString> headers() override;

    /**
     * @brief getCreativeGroups
     *
     * Получение творческих коллективов.
     * Ответ приходит в: signal listenCreative
     */
    void getVersions();

signals:
    void versionsLoad(OSMVersionsModel versions);
};


#endif //AVIA_OSMNETREPOSITORY_H
