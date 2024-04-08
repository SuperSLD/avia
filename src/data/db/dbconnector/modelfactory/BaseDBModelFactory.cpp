//
// Created by Леонид Соляной on 04.04.2024.
//

#include <QJsonObject>
#include "BaseDBModelFactory.h"

BaseDBModelFactory::BaseDBModelFactory() {

}

BaseDBModelFactory::~BaseDBModelFactory() {

}

QString BaseDBModelFactory::tableName() {
    return nullptr;
}


void BaseDBModelFactory::setConnector(DBConnector *dbConnector) {
    this->dbConnector = dbConnector;
}

BaseDBModel* BaseDBModelFactory::createModel(QJsonObject json) {
    return new BaseDBModel();
}
