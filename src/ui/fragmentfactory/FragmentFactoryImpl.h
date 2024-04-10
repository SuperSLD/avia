//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_FRAGMENTFACTORYIMPL_H
#define AVIA_FRAGMENTFACTORYIMPL_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/navigation/base/basefragmentfactory/BaseFragmentFactory.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/data/db/dbconnector/DBConnector.h"

namespace screens {

    static const QString SPLASH_SCREEN = "splash";
    static const QString MAIN_SCREEN = "main";
    static const QString CHANGE_CONNECTION_SCREEN = "change_connection";
    static const QString MODEL_DETAIL_SCREEN = "model_detail_connection";
}

class FragmentFactoryImpl: public BaseFragmentFactory {

public:
    FragmentFactoryImpl();
    ~FragmentFactoryImpl();

    BaseFragment* create(QString tag) override;
    QString createStart() override;
};


#endif //AVIA_FRAGMENTFACTORYIMPL_H
