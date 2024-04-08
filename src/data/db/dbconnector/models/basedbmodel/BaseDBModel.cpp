//
// Created by Леонид Соляной on 04.04.2024.
//

#include "BaseDBModel.h"


BaseDBModel::BaseDBModel() {

}

BaseDBModel::~BaseDBModel() {

}

QString BaseDBModel::getId() {
    return "0";
}

QList<PreviewItem> BaseDBModel::getPreview() {
    return QList<PreviewItem>();
}
