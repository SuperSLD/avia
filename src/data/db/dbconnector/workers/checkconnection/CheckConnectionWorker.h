//
// Created by Леонид Соляной on 04.04.2024.
//

#ifndef AVIA_CHECKCONNECTIONWORKER_H
#define AVIA_CHECKCONNECTIONWORKER_H

#include <QThread>

class CheckConnectionWorker: public QThread {
    Q_OBJECT

private:
    QString uriString;

public:

    CheckConnectionWorker(QString uriStr) {
        this->uriString = uriStr;
    }

    void run() override;

signals:
    void resultReady(bool isConnected);
};


#endif //AVIA_CHECKCONNECTIONWORKER_H
