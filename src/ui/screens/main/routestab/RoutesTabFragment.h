//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_ROUTESTABFRAGMENT_H
#define AVIA_ROUTESTABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/data/settings/SettingsRepository.h"

class RoutesTabFragment: public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;

public:
    RoutesTabFragment();
    ~RoutesTabFragment();

    void onResume() override;
};


#endif //AVIA_ROUTESTABFRAGMENT_H
