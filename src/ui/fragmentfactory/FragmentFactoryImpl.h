//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_FRAGMENTFACTORYIMPL_H
#define AVIA_FRAGMENTFACTORYIMPL_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/navigation/base/basefragmentfactory/BaseFragmentFactory.h"

namespace screens {

    static const QString SPLASH_SCREEN = "splash";
    static const QString MAIN_SCREEN = "main";
}

class FragmentFactoryImpl: public BaseFragmentFactory {

public:
    FragmentFactoryImpl();
    ~FragmentFactoryImpl();

    BaseFragment* create(QString tag) override;
    QString createStart() override;
};


#endif //AVIA_FRAGMENTFACTORYIMPL_H
