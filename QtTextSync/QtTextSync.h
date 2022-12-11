#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtTextSync.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include<iostream>
#include <QTimer>
class QtTextSync : public QMainWindow
{
    Q_OBJECT
        QString currentIP = "192.168.43.1";

public:
    QtTextSync(QWidget* parent = nullptr);
    ~QtTextSync();
    void UpdateText(QString newText);
    void UpdateServerUrl(QString ip);
private:
    void pullTextAndUpdate();

private:
    Ui::QtTextSyncClass ui;
    QNetworkAccessManager* manager;
    QNetworkRequest request;
    QTimer* timer;
};
