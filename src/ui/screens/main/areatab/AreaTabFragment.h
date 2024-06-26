//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_AREATABFRAGMENT_H
#define AVIA_AREATABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/ui/common/widgets/map/MapWidget.h"
#include "src/data/net/osmnetrepository/OSMNetRepository.h"
#include "src/ui/common/widgets/analytictable/AnalyticTable.h"
#include "src/ui/common/widgets/textedit/TextEdit.h"
#include "src/ui/common/widgets/button/Button.h"

class AreaTabFragment : public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;
    AnalyticTable *table;
    TextEdit *diffEdit;
    Button *addAirportsButton;

    TransportGraphModel graph;

    OSMNetRepository *netRep;

    Area area;

    int progress = 0;

public:
    AreaTabFragment();
    ~AreaTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
    void onAirportsLoaded(TransportGraphModel graph, bool fromDB);
    void onAirportsLoadedChangeProgress(int progress);

    void startCalculation();
    void addAirports();
    void onAreaCalculated(Area area);
    void onChangeCalculateAreaProgress(int progress);
    void onNewAirportsChangeProgress(int progress);
    void onAllNewAirportsCalculated();
};

#endif //AVIA_AREATABFRAGMENT_H
