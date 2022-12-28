#pragma once

#include <QDialog>
#include "ui_SetIpPortDialog.h"

class SetIpPortDialog : public QDialog
{
    Q_OBJECT
    std::function<void(QString, int)> submitListener = nullptr;

  public:
    SetIpPortDialog(QWidget *parent, QString ip, int port);
	void setOnSubmitListener(std::function<void(QString,int)> v);
	~SetIpPortDialog();

  private:
	Ui::SetIpPortDialogClass ui;
    LiveData<QString> ipStringLive = "localhost";
  LiveData<int> portLive = 8080;

};
