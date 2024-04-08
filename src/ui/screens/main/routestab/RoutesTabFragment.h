//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_ROUTESTABFRAGMENT_H
#define AVIA_ROUTESTABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/ui/common/widgets/table/Table.h"

class RoutesTabFragment: public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;
    Table *table;

public:
    RoutesTabFragment();
    ~RoutesTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
};


#endif //AVIA_ROUTESTABFRAGMENT_H
