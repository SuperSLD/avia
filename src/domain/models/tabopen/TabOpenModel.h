//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_TABOPENMODEL_H
#define AVIA_TABOPENMODEL_H

#include "src/ui/common/navigation/base/basemodel/BaseModel.h"

class TabOpenModel: public BaseModel {

private:
    int tabId;

public:
    TabOpenModel(int tabId) {
        this->tabId = tabId;
    }

    int getTabId() {
        return tabId;
    }
};

#endif //AVIA_TABOPENMODEL_H
