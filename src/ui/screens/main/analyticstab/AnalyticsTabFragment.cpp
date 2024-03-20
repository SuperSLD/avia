//
// Created by Леонид Соляной on 20.03.2024.
//

#include "AnalyticsTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

AnalyticsTabFragment::AnalyticsTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Статистика", "analytics", "analytics_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainContainer->addWidget(contentFrame);
}

AnalyticsTabFragment::~AnalyticsTabFragment() {

}
