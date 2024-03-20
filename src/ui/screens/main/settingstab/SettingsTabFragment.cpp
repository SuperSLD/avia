//
// Created by Леонид Соляной on 18.03.2024.
//

#include "SettingsTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

SettingsTabFragment::SettingsTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Настройки", "settings", "settings_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainContainer->addWidget(contentFrame);
}

SettingsTabFragment::~SettingsTabFragment() {

}
