//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_BASEREP_H
#define AVIA_BASEREP_H

#include <QHash>

class BaseRep {

public:
    BaseRep() {}

    virtual QHash<QString, QString> headers() {
        return QHash<QString, QString>();
    };
};

#endif //AVIA_BASEREP_H
