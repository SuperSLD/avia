//
// Created by Леонид Соляной on 15.05.2024.
//

#ifndef AVIA_TABLECELLWIDGET_H
#define AVIA_TABLECELLWIDGET_H


#include <QFrame>

class TableCellWidget: public QFrame {
    Q_OBJECT

public:
    TableCellWidget(
            QList<QList<QString>> table, bool firstIsBig
    );
    ~TableCellWidget();
};

#endif //AVIA_TABLECELLWIDGET_H
