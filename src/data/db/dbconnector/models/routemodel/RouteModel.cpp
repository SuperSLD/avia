//
// Created by Леонид Соляной on 09.04.2024.
//

#include "RouteModel.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

RouteModel::RouteModel(
        QJsonObject original,
        QString id,
        QString fnia,
        QString fid,
        RouteDataModel data
) {
    this->original = original;
    this->id = id;
    this->fnia = fnia;
    this->fid = fid;
    this->data = data;
}

QString RouteModel::getId() {
    return id;
}

QList<PreviewItem> RouteModel::getPreview() {

    QList<PreviewItem> preview;
    preview.append(PreviewItem("text", data.current.apdstia, colorBlack(), 18, 2, true));
    preview.append(PreviewItem("text", data.current.arrival_utc, colorTextGray(), 14, 3));
    preview.append(PreviewItem("icon", "arrow", colorTextGray()));
    preview.append(PreviewItem("text", data.current.aporgia, colorBlack(), 18, 2, true));
    preview.append(PreviewItem("text", data.current.deps_utc, colorTextGray(), 14, 3));
    preview.append(PreviewItem("text", "", colorBlack(), 18, 2, true));
    preview.append(PreviewItem("text", "Количество точек: " + QString::number(data.list.size()), colorBlack(), 18, 10));
    return preview;
}

