//
// Created by Леонид Соляной on 08.04.2024.
//

#include "FlightModel.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

FlightModel::FlightModel(QJsonObject original, QString id, QString passedTime, QString airport, QString type, FlightDataModel data) {
    this->original = original;
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
    preview.append(PreviewItem("text", data.act, colorBlack(), 18, 4, true));
    preview.append(PreviewItem("text", data.apdstci, colorBlack(), 18, 7));
    preview.append(PreviewItem("text", data.apdstia, colorPrimary(), 18, 2, true));
    preview.append(PreviewItem("text", data.arrival_utc, colorTextGray(), 14, 3));
    preview.append(PreviewItem("icon", "arrow", colorTextGray()));
    preview.append(PreviewItem("text", data.aporgci, colorBlack(), 18, 7));
    preview.append(PreviewItem("text", data.aporgia, colorPrimary(), 18, 2, true));
    preview.append(PreviewItem("text", data.deps_utc, colorTextGray(), 14, 3));
    return preview;
}

QList<DetailItem> FlightModel::getDetail() {
    QList<DetailItem> detail;
    detail.append(DetailItem("id", "Идентификатор", id));
    detail.append(DetailItem("passedTime", "", passedTime));
    detail.append(DetailItem("airport", "Аэропорт", airport));
    detail.append(DetailItem("type", "Тип", type));
    detail.append(DetailItem("fid", "", data.fid));
    detail.append(DetailItem("accl", "", QString::number(data.accl)));
    detail.append(DetailItem("accountry", "Код страны", data.accountry));
    detail.append(DetailItem("acd", "Модель самолета", data.acd));
    detail.append(DetailItem("acr", "Номер самолета", data.acr));
    detail.append(DetailItem("act", "Сокращенная модель", data.act));
    detail.append(DetailItem("alia", "Код компании", data.alia));
    detail.append(DetailItem("alic", "Код компании", data.alic));
    detail.append(DetailItem("alna", "Название компании", data.alna));
    detail.append(DetailItem("alt", "", QString::number(data.alt)));
    detail.append(DetailItem("apdstci", "Город вылета", data.apdstci));
    detail.append(DetailItem("apdstco", "Страна вылета", data.apdstco));
    detail.append(DetailItem("apdstia", "Аэропорт вылета", data.apdstia));
    detail.append(DetailItem("apdstic", "", data.apdstic));
    detail.append(DetailItem("apdstla", "", QString::number(data.apdstla)));
    detail.append(DetailItem("apdstlo", "", QString::number(data.apdstlo)));
    detail.append(DetailItem("apdstna", "", data.apdstna));
    detail.append(DetailItem("apdstst", "", data.apdstst));
    detail.append(DetailItem("apdsttz", "", QString::number(data.apdsttz)));
    detail.append(DetailItem("apdsttznl", "", data.apdsttznl));
    detail.append(DetailItem("apdsttzns", "", data.apdsttzns));
    detail.append(DetailItem("aporgci", "Город прилета", data.aporgci));
    detail.append(DetailItem("aporgco", "Страна прилета", data.aporgco));
    detail.append(DetailItem("aporgia", "Аэропорт прилета", data.aporgia));
    detail.append(DetailItem("aporgia", "", data.apdstst));
    detail.append(DetailItem("apdsttz", "", QString::number(data.apdsttz)));
    detail.append(DetailItem("aporgtznl", "", data.aporgtznl));
    detail.append(DetailItem("aporgtzns", "", data.aporgtzns));
    detail.append(DetailItem("arrau", "", data.arrau));
    detail.append(DetailItem("arrdeld", "", data.arrdeld));
    detail.append(DetailItem("arrdelr", "", data.arrdelr));
    detail.append(DetailItem("arre", "", data.arre));
    detail.append(DetailItem("arresu", "", data.arresu));
    detail.append(DetailItem("arrgate", "", data.arrgate));
    detail.append(DetailItem("arrs", "", data.arrs));
    detail.append(DetailItem("arrsu", "", data.arrsu));
    detail.append(DetailItem("arrterm", "", data.arrterm));
    detail.append(DetailItem("bl", "", data.bl ? "true" : "false"));

    detail.append(DetailItem("distance", "Дистанция", QString::number(data.distance.toInt() / 1000)));
    detail.append(DetailItem("duration", "Продолжительность", data.duration));
    detail.append(DetailItem("durationTs", "Продолжительность (час)", QString::number(data.durationTs / 60 / (double) 60)));
    return detail;
}