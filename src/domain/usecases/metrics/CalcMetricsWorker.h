//
// Created by Леонид Соляной on 13.05.2024.
//

#ifndef AVIA_CALCMETRICSWORKER_H
#define AVIA_CALCMETRICSWORKER_H


#include <QThread>
#include "src/data/settings/SettingsRepository.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/domain/models/area/Area.h"
#include "src/data/db/dbconnector/models/metrics/MetricsModel.h"

class CalcMetricsWorker: public QThread {
    Q_OBJECT

private:
    SettingsRepository *settingsRepository;
    QString id;
    bool isActive = true;
    bool dataChanged = false;

    TransportGraphModel originalGraph;
    bool originalGraphLoaded = false;

    Area area;
    bool areaLoaded = false;

    QHash<QString, TransportGraphModel> graphs;

public:
    CalcMetricsWorker() {
        id = QUuid::createUuid().toString().mid(1, 5).toUpper();
        settingsRepository = new SettingsRepository();
    }

    ~CalcMetricsWorker() {
        delete settingsRepository;
    }

    void run() override;
    void disable();

public slots:
    void areaLoad(Area area);
    void airportsLoad(TransportGraphModel graph, bool fromDB);
    void onGraphLoaded(QString key, TransportGraphModel graph);

signals:
    void metricsUpdated(MetricsModel metrics);
};



#endif //AVIA_CALCMETRICSWORKER_H
