//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEGRAPHWORKER_H
#define AVIA_CALCULATEGRAPHWORKER_H


#include <QThread>

class CalculateGraphWorker: public QThread {
    Q_OBJECT

private:

public:
    CalculateGraphWorker();
};


#endif //AVIA_CALCULATEGRAPHWORKER_H
