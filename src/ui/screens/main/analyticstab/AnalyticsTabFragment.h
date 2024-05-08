//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_ANALYTICSTABFRAGMENT_H
#define AVIA_ANALYTICSTABFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/data/db/dbconnector/modelfactory/flightmodelsfactory/FlightModelsFactory.h"
#include "src/data/db/dbconnector/modelfactory/routesmodelfactory/RoutesModelFactory.h"
#include "src/data/db/dbconnector/models/flightmodel/FlightModel.h"
#include "src/ui/common/widgets/analytictable/AnalyticTable.h"
#include "src/domain/models/analytics/AnalyticsModel.h"

class AnalyticsTabFragment: public BaseFragment {
    Q_OBJECT

private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;

    FlightModelsFactory *flightsFactory = new FlightModelsFactory();
    RoutesModelFactory *routesFactory = new RoutesModelFactory();

    AnalyticTable *table;
    AnalyticsModel analyticsModel;
    bool analyticsLoaded = false;
    int progress = 0;

    TransportGraphModel originalGraph;
    bool originalGraphLoaded = false;

    Area area;
    bool areaLoaded = false;
    QHash<QString, TransportGraphModel> graphs;

    void setAnalytics();

public:
    AnalyticsTabFragment();
    ~AnalyticsTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
    void onAnalyticsLoaded(AnalyticsModel analyticsModel);
    void onAnalyticsLoadedChangeProgress(int progress);

    void onAreaCalculated(Area area);
    void onAirportsLoaded(TransportGraphModel graph, bool fromDB);
    void onGraphCalculated(QString key, TransportGraphModel graph);
};

#endif //AVIA_ANALYTICSTABFRAGMENT_H
