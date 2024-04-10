//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_MODELDETAILFRAGMENT_H
#define AVIA_MODELDETAILFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class ModelDetailFragment: public BaseFragment {
    Q_OBJECT
private:
    SettingsRepository *settingsRep = new SettingsRepository();
    BaseDBModel *dbModel;

    QHBoxLayout *headerContainer;
    QVBoxLayout *rowsContainer;

public:
    ModelDetailFragment();
    ~ModelDetailFragment();

    void bindData(BaseModel* model) override;

private slots:
    void onBack();
    void onEdit();

};


#endif //AVIA_MODELDETAILFRAGMENT_H
