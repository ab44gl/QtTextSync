#pragma once
#include <QNetworkReply>
class NetworkHelper
{
  public:
    struct Message
    {
        QString dataString = "";
        QString errorString = "";
        bool isPost = false;
        bool isError = false;
        QString toString()
        {
            QString out;
            QTextStream ts(&out);
            ts << "isPost:" << isPost << "\n";
            ts << "isError:" << isError << "\n";
            ts << "data:" << dataString << "\n";
            ts << "error:" << errorString << "\n";
            return out;
        }
    };
    using MessageFun = void(Message);

  protected:
    QString _ip = "localhost";
    int _port = 8080;
    QNetworkAccessManager *_manager;
    std::function<MessageFun> _onMessageListener = nullptr;

  public:
    NetworkHelper(QWidget *widget);
    ~NetworkHelper();
    void setOnMessageListener(std::function<MessageFun> listener);
    void setIpPort(QString ip = "localhost", int port = 8080);
    void get();
    void post(QString msg);
};
