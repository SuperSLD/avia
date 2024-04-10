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

QList<DetailItem> RouteModel::getDetail() {
    QList<DetailItem> detail;
    detail.append(DetailItem("id", "Идентификатор", id));
    detail.append(DetailItem("fnia", "", fnia));
    detail.append(DetailItem("fid", "", fid));
    detail.append(DetailItem("fid", "", data.current.fid));
    detail.append(DetailItem("accl", "", QString::number(data.current.accl)));
    detail.append(DetailItem("accountry", "Код страны", data.current.accountry));
    detail.append(DetailItem("acd", "Модель самолета", data.current.acd));
    detail.append(DetailItem("acr", "Номер самолета", data.current.acr));
    detail.append(DetailItem("act", "Сокращенная модель", data.current.act));
    detail.append(DetailItem("alia", "Код компании", data.current.alia));
    detail.append(DetailItem("alic", "Код компании", data.current.alic));
    detail.append(DetailItem("alna", "Название компании", data.current.alna));
    detail.append(DetailItem("alt", "", QString::number(data.current.alt)));
    detail.append(DetailItem("apdstci", "Город вылета", data.current.apdstci));
    detail.append(DetailItem("apdstco", "Страна вылета", data.current.apdstco));
    detail.append(DetailItem("apdstia", "Аэропорт вылета", data.current.apdstia));
    detail.append(DetailItem("apdstic", "", data.current.apdstic));
    detail.append(DetailItem("apdstla", "", QString::number(data.current.apdstla)));
    detail.append(DetailItem("apdstlo", "", QString::number(data.current.apdstlo)));
    detail.append(DetailItem("apdstna", "", data.current.apdstna));
    detail.append(DetailItem("apdstst", "", data.current.apdstst));
    detail.append(DetailItem("apdsttz", "", QString::number(data.current.apdsttz)));
    detail.append(DetailItem("apdsttznl", "", data.current.apdsttznl));
    detail.append(DetailItem("apdsttzns", "", data.current.apdsttzns));
    detail.append(DetailItem("aporgci", "Город прилета", data.current.aporgci));
    detail.append(DetailItem("aporgco", "Страна прилета", data.current.aporgco));
    detail.append(DetailItem("aporgia", "Аэропорт прилета", data.current.aporgia));
    detail.append(DetailItem("aporgia", "", data.current.apdstst));
    return detail;
}

