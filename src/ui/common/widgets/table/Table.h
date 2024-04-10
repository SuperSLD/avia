//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_TABLE_H
#define AVIA_TABLE_H

#include <QString>
#include <QList>
#include <QWidget>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QLabel>
#include "src/data/db/dbconnector/DBConnector.h"
#include "src/data/db/dbconnector/modelfactory/BaseDBModelFactory.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/ui/common/widgets/waitingspinner/WaitingSpinnerWidget.h"

class Table: public QWidget {
    Q_OBJECT

private:

    static const int PAGE_SIZE = 30;

    int currentPage = 0;
    QLabel *currentPageLabel;
    WaitingSpinnerWidget *loader;

    DBConnector *dbConnector;
    QVBoxLayout *rowsContainer;

    BaseDBModelFactory *modelFactory;
    SettingsRepository *settingsRep = new SettingsRepository();

    void clearList(QLayout *list);

public:
    Table(BaseDBModelFactory *modelFactory);
    ~Table();

    void setConnector(DBConnector *connector);

private slots:
    void onPageLoaded(QJsonArray array, QString table);
    void onButtonClicked(QString name);
    void handleModelOpen(BaseDBModel *model);

signals:
    void onModelOpen(BaseDBModel *model);
};

#endif //AVIA_TABLE_H
