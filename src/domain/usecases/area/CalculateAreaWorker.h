//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEAREAWORKER_H
#define AVIA_CALCULATEAREAWORKER_H

#include <QThread>
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/data/net/osmnetrepository/OSMNetRepository.h"

class CalculateAreaWorker: public QThread {
    Q_OBJECT

private:
    const double DISTANCE_BETWEEN_POINT = 0.1;

    QString uriString;
    TransportGraphModel graph;

    OSMNetRepository *netRep;
    bool requestFinished = false;

public:
    CalculateAreaWorker(QString uri, TransportGraphModel graph) {
        netRep = new OSMNetRepository;
        connect(
                netRep,
                &OSMNetRepository::directionsLoad,
                this,
                &CalculateAreaWorker::directionLoad
        );

        this->uriString = uri;
        this->graph = graph;
    }

    ~CalculateAreaWorker() {
        delete netRep;
    }

    void run() override;

private slots:
    void directionLoad(OSMDirectionModel direction);

signals:
    void resultReady();
};


#endif //AVIA_CALCULATEAREAWORKER_H
