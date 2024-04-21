//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_AREATABFRAGMENT_H
#define AVIA_AREATABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/ui/common/widgets/map/MapWidget.h"

class AreaTabFragment : public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;

    MapWidget *map;

    bool dataLoaded = false;
    int progress = 0;

public:
    AreaTabFragment();
    ~AreaTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
    void onAirportsLoaded(QList<AirportModel> airports);
    void onAirportsLoadedChangeProgress(int progress);
};

#endif //AVIA_AREATABFRAGMENT_H
