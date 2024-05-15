//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_NUMBERCELLWIDGET_H
#define AVIA_NUMBERCELLWIDGET_H

#include <QFrame>

class NumberCellWidget: public QFrame {
    Q_OBJECT

public:
    NumberCellWidget(
            QString value,
            QString name,
            QString color
    );
    ~NumberCellWidget();
};


#endif //AVIA_NUMBERCELLWIDGET_H
