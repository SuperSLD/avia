//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_TEXTEDIT_H
#define AVIA_TEXTEDIT_H


#include <QWidget>
#include <QLineEdit>

class TextEdit: public QWidget {
    Q_OBJECT

private:
    QLineEdit *lineEdit;

public:
    TextEdit(QString id, QString hint, bool isPassword = false, int maxSize = 1000);
    ~TextEdit();

    void setText(QString text);
    QString text();
};


#endif //AVIA_TEXTEDIT_H
