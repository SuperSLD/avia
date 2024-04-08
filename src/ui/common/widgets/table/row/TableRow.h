//
// Created by Леонид Соляной on 08.04.2024.
//

#ifndef AVIA_TABLEROW_H
#define AVIA_TABLEROW_H


#include <QFrame>
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class TableRow: public QFrame {
    Q_OBJECT

public:
    TableRow(BaseDBModel *model, bool isGray);
    ~TableRow();
};


#endif //AVIA_TABLEROW_H
