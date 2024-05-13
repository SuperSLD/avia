//
// Created by Леонид Соляной on 13.05.2024.
//

#include "CalcMetricsWorker.h"

void CalcMetricsWorker::run() {
    while (isActive) {
        qDebug() << "CalcMetricsWorker новая итерация" << id << (originalGraphLoaded?"T":"F") << (areaLoaded?"T":"F") << graphs.size();
        if (dataChanged && areaLoaded && originalGraphLoaded && graphs.size() > 0) {
            qDebug() << "CalcMetricsWorker данные изменились" << id;
            dataChanged = false;
            auto metrics = MetricsModel(
                originalGraph,
                graphs.values(),
                area
            );
            emit metricsUpdated(metrics);
        }
        sleep(5);
    }
}

void CalcMetricsWorker::areaLoad(Area area) {
    this->area = area;
    areaLoaded = true;
    dataChanged = true;
}

void CalcMetricsWorker::airportsLoad(TransportGraphModel graph, bool fromDB) {
    originalGraph = graph;
    originalGraphLoaded = true;
    dataChanged = true;
}

void CalcMetricsWorker::onGraphLoaded(QString key, TransportGraphModel graph) {
    graphs[key] = graph;
    dataChanged = true;
}

void CalcMetricsWorker::disable() {
    qDebug() << "CalcMetricsWorker disable" << id;
    isActive = false;
}
