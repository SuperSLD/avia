//
// Created by Леонид Соляной on 08.04.2024.
//

#include "FlightModel.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

FlightModel::FlightModel(QString id, QString passedTime, QString airport, QString type, FlightDataModel data) {
    this->id = id;
    this->passedTime = passedTime;
    this->airport = airport;
    this->type = type;
    this->data = data;
}

QString FlightModel::getId() {
    return id;
}

QList<PreviewItem> FlightModel::getPreview() {
    QList<PreviewItem> preview;
    preview.append(PreviewItem("text", data.act, colorBlack(), 18, 4));
    preview.append(PreviewItem("text", data.apdstci, colorBlack(), 18, 7));
    preview.append(PreviewItem("text", data.apdstia, colorPrimary(), 18, 3, true));
    preview.append(PreviewItem("text", data.arrival_utc, colorTextGray(), 14, 3));
    preview.append(PreviewItem("icon", "arrow", colorTextGray()));
    preview.append(PreviewItem("text", data.aporgci, colorBlack(), 18, 7));
    preview.append(PreviewItem("text", data.aporgia, colorPrimary(), 18, 3, true));
    preview.append(PreviewItem("text", data.deps_utc, colorTextGray(), 14, 3));
    return preview;
}
