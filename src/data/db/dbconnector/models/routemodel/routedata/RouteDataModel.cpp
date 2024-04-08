//
// Created by Леонид Соляной on 09.04.2024.
//

#include "RouteDataModel.h"
#include <QList>

RouteDataModel::RouteDataModel(FlightDataModel current, QList<RoutePointModel> list, QString type) {
    this->current = current;
    this->list = list;
    this->type = type;
}

RouteDataModel::RouteDataModel() {}
