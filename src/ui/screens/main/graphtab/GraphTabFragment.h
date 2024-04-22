//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_GRAPHTABFRAGMENT_H
#define AVIA_GRAPHTABFRAGMENT_H

#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"

class GraphTabFragment : public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;

    int progress = 0;

    TransportGraphModel graph;

public:
    GraphTabFragment();
    ~GraphTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
    void onAirportsLoaded(TransportGraphModel graph);
    void onAirportsLoadedChangeProgress(int progress);

    void startCalculation();
    void onGraphCalculated();
};

#endif //AVIA_GRAPHTABFRAGMENT_H
