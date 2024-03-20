//
// Created by Леонид Соляной on 18.03.2024.
//

#ifndef AVIA_TOOLBAR_H
#define AVIA_TOOLBAR_H


#include <QWidget>

class Toolbar: public QWidget {
    Q_OBJECT

public:
    Toolbar(QString title, QString icon, QString iconDark);
    ~Toolbar();
};


#endif //AVIA_TOOLBAR_H
