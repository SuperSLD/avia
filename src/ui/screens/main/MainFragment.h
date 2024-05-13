//
// Created by Леонид Соляной on 03.02.2024.
//

#ifndef AVIA_MAINFRAGMENT_H
#define AVIA_MAINFRAGMENT_H

#include <QLabel>
#include <QStackedWidget>
#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/ui/common/widgets/menutabbutton/MenuTabButton.h"
#include "src/data/db/dbconnector/DBConnector.h"
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class MainFragment: public BaseFragment {
    Q_OBJECT

private:

    DBConnector *connector = nullptr;

    SettingsRepository *settingsRep = new SettingsRepository();

    const int FLIGHTS = 0;
    const int ROUTES = 1;
    const int CALCULATE_GRAPH = 2;
    const int CALCULATE_AREA = 3;
    const int MAP = 4;
    const int ANALYTICS = 5;
    const int SETTINGS = 6;

    QLabel *infoUrl;

    QStackedWidget *tabs;
    QList<BaseFragment*> tabFragments;
    QList<MenuTabButton*> tabButtons;

    bool airportsLoadingStarted = false;

private slots:
    void onTabButtonClicked(int id);
    void onThemeSwitched();
    void onOpenChangeConnection();
    void onOpenModelDetail(BaseDBModel *model);

public:
    MainFragment();
    ~MainFragment();

    void bindData(BaseModel* model) override;
    void onResume() override;
    void onPause() override;
    void onDestroy() override;
};

#endif //AVIA_MAINFRAGMENT_H
