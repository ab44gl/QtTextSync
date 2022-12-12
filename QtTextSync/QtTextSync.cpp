#include"stdafx.h"
#include "QtTextSync.h"
#include <qthread.h>
#include "DialogSetIP.h"

QtTextSync::QtTextSync(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    manager = new QNetworkAccessManager();
    manager->setTransferTimeout(30000);
    UpdateServerUrl(currentIP);
    pullTextAndUpdate();
    // event
    {
        // http request
        QObject::connect(
            manager, &QNetworkAccessManager::finished, this,
            [this](QNetworkReply* reply) {
                if (reply->operation() ==
                    QNetworkAccessManager::Operation::PostOperation) {
                    /*if (reply->error()) {
                        std::cout << "post error>"
                                <<reply->error()
                                << reply->errorString().toStdString()
                                << std::endl;
                        UpdateText("post error>" +
                reply->errorString()); return;
                }*/
                    QString msg = reply->readAll();
                    std::cout << "post msg>" << msg.toStdString() << "\n";
                    return;
                } else {
                    if (reply->error()) {
                        std::cout << "error>"
                                  << reply->errorString().toStdString()
                                  << std::endl;
                        UpdateText("error>" + reply->errorString());
                        return;
                    }

                    QString msg = reply->readAll();
                    std::cout << "msg>" << msg.toStdString() << "\n";
                    UpdateText(msg);
                }
            });
        // set ip buttton
        QObject::connect(ui.but_set_ip, &QPushButton::clicked, [this]() {
            DialogSetIP dialog(this);
            dialog.setCurrentIP(currentIP);
            dialog.setOnOkListener([this](QString ip) { UpdateServerUrl(ip); });
            dialog.exec();
        });
        // refresh buttton
        QObject::connect(ui.but_refresh, &QPushButton::clicked,
                         [this]() { pullTextAndUpdate(); });
        // post button
        QObject::connect(ui.but_post, &QPushButton::clicked, [this]() {
            QNetworkRequest request2;
            request2.setUrl(
                QUrl(QString("http://") + "localhost" + QString(":8080/")));
            request2.setHeader(request2.ContentTypeHeader, "application/text");

            auto msg = QString("this is client").toUtf8();
            manager->post(request2, msg);
        });
        // auto checkbox
        QObject::connect(ui.checkbox_auto, &QCheckBox::clicked,
                         [this](bool checked) {
                             if (checked) {
                                 timer->start(1000);
                             } else {
                                 timer->stop();
                             }
                         });
    }

    /*auto id = QThread::currentThreadId();
    std::cout << "main thread id " << id << std::endl;*/

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout,
                     [this]() { pullTextAndUpdate(); });
}

QtTextSync::~QtTextSync() {}

void QtTextSync::UpdateText(QString newText) {
    auto oldText = ui.ptxtedit_msg->toPlainText();
    if (oldText != newText) {
        ui.ptxtedit_msg->setPlainText(newText);
    }
}

void QtTextSync::UpdateServerUrl(QString ip) {
    currentIP = ip;
    request.setUrl(QUrl(QString("http://") + ip + QString(":8080/")));
    ui.label_current_ip->setText(ip + ":8080");
    pullTextAndUpdate();
}

void QtTextSync::pullTextAndUpdate() {
    auto reply = manager->get(request);
}
