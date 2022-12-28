#pragma once

#include <QMainWindow>
#include "ui_TextSync.h"
#include"LiveData.h"
#include "NetworkHelper.h"
class TextSync : public QMainWindow
{
	Q_OBJECT

public:
	TextSync(QWidget *parent = nullptr);
	~TextSync();

  protected:
    void openSetIpDialog();
    void send();
    void receive();
    QString ipPortString();

private:
	Ui::TextSyncClass ui;
	//state
    LiveData<int> portLive = 8080;
    LiveData<QString> ipStringLive = "192.168.43.1";
    LiveData<QString> sendPlainTextLive = "test send";
    LiveData<QString> receivePlainTextLive = "test receive";
    NetworkHelper *networkHelper = nullptr;


};
