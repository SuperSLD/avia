//
// Created by Леонид Соляной on 13.05.2024.
//

#ifndef AVIA_PRIORITYQUEUE_H
#define AVIA_PRIORITYQUEUE_H

#include <QMutableSetIterator>

template <typename T> class PriorityQueue {

private:
    QList<QPair<double, T>> elements;

public:
    PriorityQueue() {
        // pass //
    };

    bool isEmpty() {
        return elements.isEmpty();
    }

    bool isNotEmpty() {
        return !elements.isEmpty();
    }

    int size() {
        return elements.size();
    }

    void put(T element, double priority) {
        elements.append(QPair<double, T>(priority, element));
        for (int i = 0; i < elements.size(); i++) {
            for (int j = i; j < elements.size(); j++) {
                if (elements[j].first < elements[i].first) {
                    auto c = elements[j];
                    elements[j] = elements[i];
                    elements[i] = c;
                }
            }
        }
    }

    T get() {
        auto first = elements.first().second;
        elements.removeFirst();
        return first;
    }

    QList<QPair<double, T>> toStringPriority() {
        return elements;
    }
};

#endif //AVIA_PRIORITYQUEUE_H
