//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_DETAILITEM_H
#define AVIA_DETAILITEM_H

#include <QString>

class DetailItem {

public:
    QString paramName;
    QString paramDescription;
    QString paramValue;

    DetailItem(
            QString paramName,
            QString paramDescription,
            QString paramValue
    ) {
        this->paramName = paramName;
        this->paramDescription = paramDescription;
        this->paramValue = paramValue;
    }
};

#endif //AVIA_DETAILITEM_H
