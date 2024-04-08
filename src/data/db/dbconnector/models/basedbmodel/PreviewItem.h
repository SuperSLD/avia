//
// Created by Леонид Соляной on 08.04.2024.
//

#ifndef AVIA_PREVIEWITEM_H
#define AVIA_PREVIEWITEM_H

#include <QString>

class PreviewItem {

public:

    QString type;
    QString value;
    QString color;
    int size;
    bool isBold;
    // ширина столбца в поделенная на 20
    int width;

    PreviewItem(
            QString type,
            QString value,
            QString color = "",
            int size = 0,
            int width = 5,
            bool isBold = false
    ) {
        this->type = type;
        this->value = value;
        this->color = color;
        this->size = size;
        this->isBold = isBold;
        this->width = width;
    }
};

#endif //AVIA_PREVIEWITEM_H
