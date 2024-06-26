//
// Created by Леонид Соляной on 04.04.2024.
//

#ifndef AVIA_BASEDBMODEL_H
#define AVIA_BASEDBMODEL_H


#include <QString>
#include <QList>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "PreviewItem.h"
#include "DetailItem.h"

class BaseDBModel: public BaseModel {

public:
    BaseDBModel();
    ~BaseDBModel();

    virtual QString getId();
    virtual QList<PreviewItem> getPreview();
    virtual QList<DetailItem> getDetail();
};

#endif //AVIA_BASEDBMODEL_H
