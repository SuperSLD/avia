//
// Created by Леонид Соляной on 18.03.2024.
//

#include "FlightsTabFragment.h"
#include "src/ui/common/widgets/toolbar/Toolbar.h"

FlightsTabFragment::FlightsTabFragment() {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    this->setLayout(mainContainer);
    this->setContentsMargins(0, 0 , 0, 0);
    mainContainer->setContentsMargins(0, 0, 0, 0);

    Toolbar *toolbar = new Toolbar("Данные о перелетах", "flights", "flights_dark");
    mainContainer->addWidget(toolbar);

    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentContainer = new QVBoxLayout();
    contentFrame->setLayout(contentContainer);
    contentFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainContainer->addWidget(contentFrame);
}

FlightsTabFragment::~FlightsTabFragment() {

}
