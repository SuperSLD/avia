//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_SWITCHERVARIANT_H
#define AVIA_SWITCHERVARIANT_H


#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

class SwitcherVariant: public QPushButton {
    Q_OBJECT

private:
    QString id;
    QString text;
    QLabel *textLabel;

    void selfClick() {
        emit onSelect(text);
    }

public:
    SwitcherVariant(QString id, QString text) {
        this->id = id;
        this->text = text;
        QVBoxLayout *vb = new QVBoxLayout;
        vb->setAlignment(Qt::AlignCenter);
        this->setLayout(vb);
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        textLabel = new QLabel(text);
        vb->addWidget(textLabel);

        connect(this, &SwitcherVariant::clicked, this, &SwitcherVariant::selfClick);
    }

    ~SwitcherVariant() {
        delete textLabel;
    }

    void setSelected(bool selected) {
        if (selected) {
            textStyle(id + "t", textLabel, 16, colorWhite(), true);
            coloredCardStyle(
                    id,
                    this,
                    colorPrimary(),
                    16,
                    0
            );
        } else {
            textStyle(id + "t", textLabel, 16, colorPrimary(), true);
            coloredCardStyle(
                    id,
                    this,
                    colorWhite(),
                    0,
                    0
            );
        }
    }

    QString getText() {
        return this->text;
    }

    signals:
        void onSelect(QString text);
};

#endif //AVIA_SWITCHERVARIANT_H
