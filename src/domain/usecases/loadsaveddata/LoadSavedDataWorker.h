//
// Created by Леонид Соляной on 01.05.2024.
//

#ifndef AVIA_LOADSAVEDDATAWORKER_H
#define AVIA_LOADSAVEDDATAWORKER_H


#include <QThread>
#include "src/data/settings/SettingsRepository.h"
#include "src/domain/models/area/Area.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"

class LoadSavedDataWorker: public QThread {
    Q_OBJECT

private:
    SettingsRepository *settingsRepository;

public:
    LoadSavedDataWorker() {
        settingsRepository = new SettingsRepository();
    }

    ~LoadSavedDataWorker() {
        delete settingsRepository;
    }

    void run() override;

signals:
    void areaLolad(Area area);
    void airportsLolad(TransportGraphModel graph, bool fromDB);

};


#endif //AVIA_LOADSAVEDDATAWORKER_H
