//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEAREAWORKER_H
#define AVIA_CALCULATEAREAWORKER_H

#include <QThread>

class CalculateAreaWorker: public QThread {
    Q_OBJECT
private:

public:
    CalculateAreaWorker();
};


#endif //AVIA_CALCULATEAREAWORKER_H
