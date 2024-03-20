//
// Created by Леонид Соляной on 20.03.2024.
//

#include <QLineEdit>
#include <QHBoxLayout>
#include "TextEdit.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

TextEdit::TextEdit(QString id, QString hint, bool isPassword, int maxSize) {
    QHBoxLayout *container = new QHBoxLayout;
    container->setContentsMargins(0, 0, 0, 0);
    lineEdit = new QLineEdit();
    lineEdit->setMinimumHeight(54);
    QFont font = QFont("Roboto", 18, QFont::Normal);
    lineEdit->setFont(font);
    lineEdit->setPlaceholderText(hint);
    lineEdit->setEchoMode(isPassword ? QLineEdit::Password : QLineEdit::Normal);
    lineEdit->setMaxLength(maxSize);
    coloredCardStyle(
            id,
            lineEdit,
            colorWhite(),
            16,
            16,
            1,
            colorBorder(),
            nullptr,
            nullptr,
            "color: "+colorBlack()+";"
                  "outline: none;"
    );
    container->addWidget(lineEdit);
    this->setLayout(container);
}

TextEdit::~TextEdit() {
    delete lineEdit;
}

QString TextEdit::text() {
    return lineEdit->text();
}

void TextEdit::setText(QString text) {
    lineEdit->setText(text);
}


