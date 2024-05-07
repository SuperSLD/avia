//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_MAPTABFRAGMENT_H
#define AVIA_MAPTABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/ui/common/widgets/map/MapWidget.h"

class MapTabFragment: public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;

    MapWidget *map;

    bool dataLoaded = false;
    int progress = 0;

public:
    MapTabFragment();
    ~MapTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);

    void onAirportsLoaded(TransportGraphModel graph, bool fromDB);
    void onGraphCalculated(QString key, TransportGraphModel graph);
    void onAreaCalculated(Area area);
};


#endif //AVIA_MAPTABFRAGMENT_H
