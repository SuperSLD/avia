//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_HANDLERDATA_H
#define AVIA_HANDLERDATA_H

#include <QString>
#include <QJsonObject>
#include "BaseRep.h"

class HandlerData {

public:

    QString uuid = QUuid::createUuid().toString();
    void (*handler)(QJsonObject, BaseRep *rep);
};

#endif //AVIA_HANDLERDATA_H
