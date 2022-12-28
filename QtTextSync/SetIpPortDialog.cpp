#include "stdafx.h"
#include "SetIpPortDialog.h"
#include"Event.h"
SetIpPortDialog::SetIpPortDialog(QWidget *parent, QString ip, int port) : QDialog(parent)
{
    ui.setupUi(this);
    ui.lineEdit_port->setText(QString::number(port));
    ui.lineEdit_ip->setText(ip);
    Event::ButtonClicked(ui.pushButton_ok, [this]() {
        if (submitListener != nullptr)
        {
            auto ip = ui.lineEdit_ip->text();
            auto port = ui.lineEdit_port->text().toInt();
            submitListener(ip, port);
        }
        accept();
    });
}

void SetIpPortDialog::setOnSubmitListener(std::function<void(QString, int)> v)
{
    submitListener = v;
}

SetIpPortDialog::~SetIpPortDialog()
{
}

