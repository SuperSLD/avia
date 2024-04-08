//
// Created by Леонид Соляной on 20.03.2024.
//

#include "Table.h"
#include "src/ui/common/widgets/table/row/TableRow.h"
#include "src/ui/common/widgets/swgbutton/SwgButton.h"
#include "src/ui/common/widgets/waitingspinner/WaitingSpinnerWidget.h"

#include <src/ui/theme/AppTheme.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QString>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

using namespace theme;

Table::Table(BaseDBModelFactory *modelFactory) {
    this->modelFactory = modelFactory;

    QVBoxLayout *vContainer = new QVBoxLayout;
    vContainer->setContentsMargins(0, 0, 0, 0);
    vContainer->setSpacing(0);

    QHBoxLayout *headerContainer = new QHBoxLayout;
    vContainer->addLayout(headerContainer);
    headerContainer->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *headerLeft = new QHBoxLayout;
    headerLeft->setAlignment(Qt::AlignLeft);
    headerLeft->setContentsMargins(16, 16, 16, 16);
    QHBoxLayout *headerRight = new QHBoxLayout;
    headerRight->setAlignment(Qt::AlignRight);
    headerRight->setContentsMargins(16, 16, 16, 16);
    headerRight->setSpacing(8);

    headerContainer->addLayout(headerLeft);
    headerContainer->addLayout(headerRight);

    // Левая половина хедера
    QLabel *headerLabel = new QLabel("Просмотр таблицы");
    textStyle("headerLabel", headerLabel, 20, colorTextGray());
    headerLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    headerLeft->addWidget(headerLabel);

    // Правая половина хедера
    QWidget *loaderBox = new QWidget;
    loaderBox->setMinimumSize(QSize(36, 36));
    loaderBox->setMaximumSize(QSize(36, 36));
    loader = new WaitingSpinnerWidget(loaderBox, true, false);
    loader->setColor(colorPrimaryQt());
    loader->start();
    headerRight->addWidget(loaderBox);

    QLabel *pageSizeLabel = new QLabel("Размер страницы: " + QString::number(PAGE_SIZE));
    textStyle("pageSizeLabel", pageSizeLabel, 18, colorBlack());
    headerRight->addWidget(pageSizeLabel);

    SwgButton *previousPage = new SwgButton("arrow_button_left", QSize(36, 36), "previousPage");
    connect(previousPage, &SwgButton::onClicked, this, &Table::onButtonClicked);
    SwgButton *nextPage = new SwgButton("arrow_button_right", QSize(36, 36), "nextPage");
    headerRight->addWidget(previousPage);
    connect(nextPage, &SwgButton::onClicked, this, &Table::onButtonClicked);

    QWidget *pageCounterFrame = new QFrame;
    pageCounterFrame->setMinimumSize(QSize(36, 36));
    pageCounterFrame->setMaximumSize(QSize(36, 36));
    coloredCardStyle("pageCounterFrame", pageCounterFrame, colorWhite(), 8, 0, 1, colorPrimary());
    QVBoxLayout *pageCounterContainer = new QVBoxLayout;
    pageCounterContainer->setContentsMargins(0, 0, 0, 0);
    pageCounterContainer->setAlignment(Qt::AlignCenter);
    pageCounterFrame->setLayout(pageCounterContainer);
    currentPageLabel = new QLabel("0");
    textStyle("currentPage", currentPageLabel, 18, colorBlack());
    pageCounterContainer->addWidget(currentPageLabel);
    headerRight->addWidget(pageCounterFrame);

    headerRight->addWidget(nextPage);

    QWidget *line = new QWidget();
    line->setMinimumHeight(1);
    line->setMaximumHeight(1);
    coloredCardStyle("line", line, colorBorder(), 0, 0);
    vContainer->addWidget(line);

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

Table::~Table() {
    delete modelFactory;
    delete settingsRep;
}

void Table::setConnector(DBConnector *connector) {
    disconnect(dbConnector, &DBConnector::onPageLoaded, this, &Table::onPageLoaded);
    this->dbConnector = connector;
    connect(dbConnector, &DBConnector::onPageLoaded, this, &Table::onPageLoaded);
    this->modelFactory->setConnector(connector);
    dbConnector->loadPage(modelFactory->tableName(), currentPage, PAGE_SIZE);
}

void Table::onPageLoaded(QJsonArray array, QString table) {
    if (table == modelFactory->tableName()) {
        qDebug() << "Table::onPageLoaded" << array.size();
        clearList(rowsContainer);
        loader->stop();
        int i = 0;
                foreach(QJsonValue val, array) {
                BaseDBModel *model = modelFactory->createModel(val.toObject());
                rowsContainer->addWidget(new TableRow(model, i % 2 != 0));
                i++;
            }
    }
}

void Table::clearList(QLayout *list) {
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

void Table::onButtonClicked(QString name) {
    if (name == "previousPage") {
        if (currentPage > 0) {
            currentPage--;
        }
    } else if (name == "nextPage") {
        currentPage++;
    }
    loader->start();
    currentPageLabel->setText(QString::number(currentPage));
    dbConnector->loadPage(modelFactory->tableName(), currentPage, PAGE_SIZE);
}
