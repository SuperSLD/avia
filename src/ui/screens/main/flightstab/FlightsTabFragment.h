//
// Created by Леонид Соляной on 18.03.2024.
//

#ifndef AVIA_FLIGHTSTABFRAGMENT_H
#define AVIA_FLIGHTSTABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/data/settings/SettingsRepository.h"

class FlightsTabFragment: public BaseFragment {
    Q_OBJECT

private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;

public:
    FlightsTabFragment();
    ~FlightsTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
};


#endif //AVIA_FLIGHTSTABFRAGMENT_H
