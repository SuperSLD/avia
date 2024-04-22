//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEAREAWORKER_H
#define AVIA_CALCULATEAREAWORKER_H

#include <QThread>
#include "src/domain/models/transportgraph/TransportGraphModel.h"

class CalculateAreaWorker: public QThread {
    Q_OBJECT

private:
    QString uriString;
    TransportGraphModel graph;

public:
    CalculateAreaWorker(QString uri, TransportGraphModel graph) {
        this->uriString = uri;
        this->graph = graph;
    }

    void run() override;

signals:
    void resultReady();
};


#endif //AVIA_CALCULATEAREAWORKER_H
