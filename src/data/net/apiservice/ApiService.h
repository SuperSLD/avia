//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_APISERVICE_H
#define AVIA_APISERVICE_H


#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QList>
#include <QNetworkReply>
#include <QUuid>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "HandlerData.h"

class ApiService: public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager *networkManager;
    QList<HandlerData> handlers;
    BaseRep *rep;
    bool debug;
    QString baseUrl;

    /**
     * @brief createRequest
     *
     * Создание запроса для сервера.
     *
     * @param url путь
     * @return реквест для отправки.
     */
    QNetworkRequest createRequest(QString url) {
        qDebug() << "AppNetworkService: make request";
        qDebug() << "AppNetworkService: " << baseUrl + "/" + url;
        QNetworkRequest request(QUrl(baseUrl + "/" + url));
        request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                QStringLiteral("application/json;charset=utf-8")
        );
        auto requestHeaders = rep->headers();
        foreach(auto header, requestHeaders.keys()) {
            request.setRawHeader(header.toUtf8(), requestHeaders[header].toUtf8());
        }
        return request;
    }

    /**
     * @brief createResponseHandler
     *
     * Создание колбэка, который
     * будет ждать ответ сервера.
     *
     * @return UUID колбэка.
     */
    QString createResponseHandler(void (*handler)(QJsonObject, BaseRep*)) {
        HandlerData handlerData = HandlerData();
        handlerData.handler = handler;
        qDebug() << "AppNetworkService: handler UUID -" << handlerData.uuid;
        handlers.append(handlerData);
        return handlerData.uuid;
    }

public:
    ApiService(QString baseUrl, BaseRep *rep, bool debug) {
        this->rep = rep;
        this->debug = debug;
        this->baseUrl = baseUrl;
        networkManager = new QNetworkAccessManager();
        connect(
                networkManager,
                &QNetworkAccessManager::finished,
                this,
                &ApiService::onHttpResult
        );
    }
    ~ApiService() {
        delete networkManager;
    }

    void get(
            QString url,
            void (*handler)(QJsonObject, BaseRep*)
    ) {
        QNetworkRequest req = createRequest(url);
        QString uuid = createResponseHandler(handler);
        QNetworkReply* reply;
        qDebug() << "AppNetworkService: GET" << uuid;
        reply = networkManager->get(req);
        reply->setProperty("request_id", uuid);
    }

    void post(
            QString url,
            void (*handler)(QJsonObject, BaseRep*),
            QJsonObject param
    ) {
        QNetworkRequest req = createRequest(url);
        QString uuid = createResponseHandler(handler);
        QNetworkReply* reply;
        qDebug() << "AppNetworkService: POST" << uuid;
        qDebug() << "AppNetworkService: BODY-" << QJsonDocument(param).toJson(QJsonDocument::Compact) << Qt::endl << "BODY uuid-" << uuid << Qt::endl;
        reply = networkManager->post(
                req, QJsonDocument(param).toJson(QJsonDocument::Compact)
        );
        reply->setProperty("request_id", uuid);
    }

private slots:
    void onHttpResult(QNetworkReply *reply) {
        QString uuid = reply->property("request_id").toString();
        qDebug() << "AppNetworkService: response UUID -" << uuid;
        HandlerData handlerData;
        int handlerIndex = -1;
        QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
        if ( statusCode.isValid() ) {
            qDebug() << "AppNetworkService: STATUS CODE -" << statusCode.toString() << uuid;
        }
        for (int i = 0; i < handlers.size(); i++) {
            if (handlers[i].uuid == uuid) {
                handlerData = handlers[i];
                handlerIndex = i;
                qDebug() << "AppNetworkService: success found handler -" << uuid;
            }
        }

        QJsonObject errorResponse;
        errorResponse.insert("success", false);

        if(!reply->error()) {
            QByteArray resp = reply->readAll();
            if (debug) qDebug() << "AppNetworkService: " << resp << uuid;
            QJsonDocument doc = QJsonDocument::fromJson(resp);
            QJsonObject obj;
            if(!doc.isNull()) {
                if(doc.isObject()) {
                    obj = doc.object();
                    qDebug() << "AppNetworkService: success parse -" << uuid;
                    handlerData.handler(obj, rep);
                } else {
                    qDebug() << "AppNetworkService: Document is not an object" << uuid;
                    errorResponse.insert("message", "Неправильный ответ сервера");
                    handlerData.handler(errorResponse, rep);
                }
            } else {
                qDebug() << "AppNetworkService: Invalid JSON...\n" << uuid;
                errorResponse.insert("message", "Неправильный ответ сервера");
                handlerData.handler(errorResponse, rep);
            }
        } else {
            qDebug() << "AppNetworkService: http response error -" << uuid;
            errorResponse.insert("message", "Ошибка подключения");
            handlerData.handler(errorResponse, rep);

        }

        // удаляем хэндлер запроса если он найден
        if (handlerIndex >= 0) {
            handlers.removeAt(handlerIndex);
            qDebug() << "AppNetworkService: handler remove -" << handlers.size();
        }
    };
};

#endif //AVIA_APISERVICE_H
