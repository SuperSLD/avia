//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_GRAPHTABFRAGMENT_H
#define AVIA_GRAPHTABFRAGMENT_H

#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/loadingcontainer/LoadingContainerWidget.h"
#include "src/ui/common/widgets/analytictable/AnalyticTable.h"
#include "src/ui/common/widgets/textedit/TextEdit.h"

class GraphTabFragment : public BaseFragment {
    Q_OBJECT
private:

    LoadingContainerWidget *loadingContainer;
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector *dbConnector;
    AnalyticTable *table;

    TextEdit *passengersPartEdit;
    TextEdit *greedEdit;
    TextEdit *gregariousnessEdit;

    int progress = 0;
    QString save = "s1";

    TransportGraphModel graph;
    bool graphLoaded = false;

    QHash<QString, TransportGraphModel> results;

public:
    GraphTabFragment();
    ~GraphTabFragment();

    void onResume() override;
    void setConnector(DBConnector *connector) override;

private slots:
    void onConnectionChecked(bool isConnected);
    void onAirportsLoaded(TransportGraphModel graph, bool fromDB);
    void onAirportsLoadedChangeProgress(int progress);
    void onCalculateGraphProgressChange(int progress);

    void startCalculation();
    void onGraphCalculated(QString key, TransportGraphModel graph);

    void onSaveSelected(QString save);
};

#endif //AVIA_GRAPHTABFRAGMENT_H
