//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEGRAPHWORKER_H
#define AVIA_CALCULATEGRAPHWORKER_H


#include <QThread>
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"

class CalculateGraphWorker: public QThread {
Q_OBJECT

private:
    QString uriString;
    TransportGraphModel graph;

public:
    CalculateGraphWorker(QString uri, TransportGraphModel graph) {
        this->uriString = uri;
        this->graph = graph;
    }

    void run() override;

signals:
    void resultReady();
};

#endif //AVIA_CALCULATEGRAPHWORKER_H
