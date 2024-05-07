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
    QString key;
    TransportGraphModel graph;

    double greed;
    double gregariousness;

    SettingsRepository *settingsRepository;

public:
    CalculateGraphWorker(QString key, TransportGraphModel graph, double greed, double gregariousness) {
        this->key = key;
        this->graph = graph;
        this->greed = greed;
        this->gregariousness = gregariousness;
        settingsRepository = new SettingsRepository();
    }

    ~CalculateGraphWorker() {
        delete settingsRepository;
    }

    void run() override;

private slots:
    void handleProgress(int progress) {
        emit onChangeProgress(progress);
    };

signals:
    void resultReady(QString key, TransportGraphModel graph);
    void onChangeProgress(int progress);
};

#endif //AVIA_CALCULATEGRAPHWORKER_H
