//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEAREAWORKER_H
#define AVIA_CALCULATEAREAWORKER_H

#include <QThread>
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/data/net/osmnetrepository/OSMNetRepository.h"
#include "src/domain/models/area/Area.h"

class CalculateAreaWorker: public QThread {
    Q_OBJECT

private:
    const double DISTANCE_BETWEEN_POINT = 0.3;

    QString uriString;
    TransportGraphModel graph;

    bool requestFinished = false;
    QString airportId;
    AreaPoint currentRequestPoint;

    double lonDif;
    double latDif;
    double currentLon;
    double currentLat;

public:
    CalculateAreaWorker(QString uri, TransportGraphModel graph) {
        this->uriString = uri;
        this->graph = graph;
    }

    void run() override;

public slots:
    void directionLoad(OSMDirectionModel direction);

signals:
    void direction(double lon1, double lat1, double lon2, double lat2);
    void resultReady(Area area);
    void onChangeProgress(int progress);
};


#endif //AVIA_CALCULATEAREAWORKER_H
