//
// Created by Леонид Соляной on 03.02.2024.
//

#ifndef AVIA_MAINFRAGMENT_H
#define AVIA_MAINFRAGMENT_H

#include <QLabel>
#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"

class MainFragment: public BaseFragment {
    Q_OBJECT

private:

    const int FLIGHTS = 0;
    const int ROUTES = 1;
    const int MAP = 2;
    const int ANALYTICS = 3;
    const int SETTINGS = 4;

    QLabel *infoUrl;

public:
    MainFragment();
    ~MainFragment();
};

#endif //AVIA_MAINFRAGMENT_H
