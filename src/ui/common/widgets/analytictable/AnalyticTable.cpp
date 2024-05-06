//
// Created by Леонид Соляной on 10.04.2024.
//

#include <QVBoxLayout>
#include "AnalyticTable.h"

#include <QScrollArea>
#include <QScrollBar>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

AnalyticTable::AnalyticTable() {
    QVBoxLayout *vContainer = new QVBoxLayout;
    vContainer->setContentsMargins(0, 0, 0, 0);
    vContainer->setSpacing(0);

    // зона прокрутки
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrollBar("scrollArea", scrollArea);
    QHBoxLayout *deskContainer = new QHBoxLayout;
    rowsContainer = new QVBoxLayout;
    rowsContainer->setSpacing(0);
    rowsContainer->setAlignment(Qt::AlignTop);
    deskContainer->addLayout(rowsContainer);
    deskContainer->setContentsMargins(0, 0, 0, 0);
    rowsContainer->setContentsMargins(0,0,0,0);
    scrolContainer->setLayout(deskContainer);
    scrollArea->setWidget(scrolContainer);
    scrollArea->setWidgetResizable(true);
    scrollArea->horizontalScrollBar()->setEnabled(false);
    scrollArea->verticalScrollBar()->hide();
    scrollArea->verticalScrollBar()->setMaximumWidth(0);

    vContainer->addWidget(scrollArea);

    this->setLayout(vContainer);
}

AnalyticTable::~AnalyticTable() {
    delete rowsContainer;
}

void AnalyticTable::setAnalytics(BaseAnalyticModel *analytics) {
    clearList(rowsContainer);
    foreach(auto row, analytics->getRows()) {
        rowsContainer->addWidget(row.getRowView());
    }
}

void AnalyticTable::clearList(QLayout *list) {
    QLayoutItem* child;
    while(list->count()!=0) {
        child = list->takeAt(0);
        if(child->layout() != 0) {
            clearList(child->layout());
        }
        else if(child->widget() != 0) {
            delete child->widget();
        }
        delete child;
    }
}
