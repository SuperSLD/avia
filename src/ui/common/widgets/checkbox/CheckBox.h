//
// Created by Леонид Соляной on 02.05.2024.
//

#ifndef AVIA_CHECKBOX_H
#define AVIA_CHECKBOX_H


#include <QPushButton>
#include "src/ui/common/widgets/swgbutton/SwgButton.h"

class CheckBox: public QFrame {
    Q_OBJECT

private:
    SwgButton *checkboxOf;
    SwgButton *checkboxOn;

    bool isChecked = false;

public:
    CheckBox(QString text, bool checked = false);

private slots:
    void selfClick(QString name);

signals:
    void onChangeState(bool checked);

};


#endif //AVIA_CHECKBOX_H
