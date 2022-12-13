#include "stdafx.h"
#include "NetworkHelper.h"

NetworkHelper::NetworkHelper(QWidget *widget)
{
    _manager = new QNetworkAccessManager(widget);
    _manager->setTransferTimeout(30000);
    // message signal
    QObject::connect(_manager, &QNetworkAccessManager::finished, widget, [this](QNetworkReply *reply) {
        Message msg;
        msg.isPost = reply->operation() == QNetworkAccessManager::Operation::PostOperation;
        msg.isError = reply->error();
        if (msg.isError)
        {
            msg.errorString = reply->errorString();
            return;
        }
        msg.dataString = reply->readAll();
        if (_onMessageListener != nullptr)
            _onMessageListener(msg);
    });
}

NetworkHelper::~NetworkHelper()
{
    delete _manager;
    _manager->deleteLater();
}

void NetworkHelper::setOnMessageListener(std::function<MessageFun> listener)
{
    this->_onMessageListener = listener;
}

void NetworkHelper::setIpPort(QString ip, int port)
{
    _ip = ip;
    _port = port;
}

void NetworkHelper::get()
{
    QNetworkRequest request(QUrl("http://" + _ip + ":" + QString(_port)));
    _manager->get(request);
}

void NetworkHelper::post(QString msg)
{
    QNetworkRequest request(QUrl("http://" + _ip + ":" + QString(_port)));
    request.setHeader(request.ContentTypeHeader, "application/text");
    _manager->post(request, msg.toUtf8());
}
