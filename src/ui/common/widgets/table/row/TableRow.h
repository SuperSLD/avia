//
// Created by Леонид Соляной on 08.04.2024.
//

#ifndef AVIA_TABLEROW_H
#define AVIA_TABLEROW_H


#include <QFrame>
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class TableRow: public QFrame {
    Q_OBJECT

private:
    BaseDBModel *model;

public:
    TableRow(BaseDBModel *model, bool isGray);
    ~TableRow();

private slots:
    void onEditButtonClicked(QString name);

signals:
    void onModelOpen(BaseDBModel *model);
};


#endif //AVIA_TABLEROW_H
