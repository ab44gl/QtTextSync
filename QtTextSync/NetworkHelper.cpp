#include "stdafx.h"
#include "NetworkHelper.h"

NetworkHelper::NetworkHelper(QWidget *widget)
{
    _manager = new QNetworkAccessManager(widget);
    _manager->setTransferTimeout(50000);
    // message signal
    QObject::connect(_manager, &QNetworkAccessManager::finished, widget, [this](QNetworkReply *reply) {
        Message msg;
        msg.isPost = reply->operation() == QNetworkAccessManager::Operation::PostOperation;
        msg.isError = reply->error() == QNetworkReply::NetworkError::NoError ? false : true;
        if (msg.isError)
        {
            msg.errorString = reply->errorString();
        }
        msg.dataString = reply->readAll();
        if (_onMessageListener != nullptr)
            _onMessageListener(msg);
    });
}

NetworkHelper::~NetworkHelper()
{
    _manager->deleteLater();
    delete _manager;
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
    QNetworkRequest request(QUrl("http://" + ipPortString()));
    request.setHeader(request.ContentTypeHeader, "application/text");
    _manager->get(request);
}

void NetworkHelper::post(QString msg)
{
    QNetworkRequest request(QUrl("http://" +ipPortString()));
    request.setHeader(request.ContentTypeHeader, "application/text");
    _manager->post(request, msg.toUtf8());
    
}

QString NetworkHelper::ipPortString()
{
    if (_port == 0)
    {
        return _ip;
    }
    return _ip + ":" + QString::number(_port);
}
