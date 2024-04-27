//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_DATAWRAPPER_H
#define AVIA_DATAWRAPPER_H


#include <QJsonObject>
#include <qstring.h>


/**
 * Общая модель ответа сервера.
 */
template <typename T> class DataWrapper {
private:
    bool success = false;
    QString message = NULL;
    T data = T(QJsonValue());

public:
    DataWrapper() {}
    DataWrapper(QJsonObject obj)  {
        this->success = obj["success"].toBool();
        this->message = obj["message"].toString();
        if (obj.contains("data")) {
            this->data = T(obj["data"]);
        }
    }
    ~DataWrapper() {}

    /**
     * @brief isSuccess
     *
     * Проверка валидности ответа
     * сервера.
     *
     * @return true если запрос прошел без ошибок.
     */
    bool isSuccess() {
        return success;
    }


    /**
     * @brief getMessage
     *
     * Ответ сервера в случае ошибки.
     *
     * @return сообщение об ошибке.
     */
    QString getMessage() {
        return message;
    }


    /**
     * @brief getData
     *
     * Получение полезной информации
     * от сервера.
     *
     * @return данные указанного типа.
     */
    T getData() {
        return data;
    }
};


#endif //AVIA_DATAWRAPPER_H
