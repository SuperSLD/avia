//
// Created by Леонид Соляной on 07.04.2024.
//

#ifndef AVIA_GETPAGEWORKER_H
#define AVIA_GETPAGEWORKER_H

#include <QString>
#include <QList>
#include <QThread>
#include <QJsonArray>

class GetPageWorker: public QThread {
    Q_OBJECT

private:
    QString uriString;
    QString table;
    int page;
    int pageSize;

public:

    GetPageWorker(
            QString uriStr,
            QString table,
            int page,
            int pageSize
    ) {
        this->uriString = uriStr;
        this->table = table;
        this->page = page;
        this->pageSize = pageSize;
    }

    void run() override;

signals:
    void resultReady(QJsonArray array, QString table);
};


#endif //AVIA_GETPAGEWORKER_H
