#include "stdafx.h"
#include "TextSync.h"
#include "Event.h"
#include "SetIpPortDialog.h"
TextSync::TextSync(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    // network helper
    {
        networkHelper = new NetworkHelper(this);
        networkHelper->setOnMessageListener([this](NetworkHelper::Message msg) {
            std::cout << msg.toString().toStdString() << std::endl;
            if (msg.isError)
            {
               QMessageBox::warning(this, "Error", msg.errorString);
            }
            else
            {
               if (!msg.isPost)
               {
                   receivePlainTextLive.set(msg.dataString);
               }
            }
        });
    }
    // all event
    {
        // set ip
        Event::ButtonClicked(ui.button_set_ip, [this]() {
            openSetIpDialog();
        });

        Event::ButtonClicked(ui.button_send, [this]() {
            send();
        });
        Event::PlainEditTextChanged(ui.plain_text_edit_send, [this](QString v) {
            sendPlainTextLive.set(v);
        });
        // receive

        Event::ButtonClicked(ui.button_receive, [this]() {
            receive();
        });
        Event::PlainEditTextChanged(ui.plain_text_edit_receive, [this](QString v) {
            receivePlainTextLive.set(v);
        });
    }
    // data observer
    {
        portLive.observe([this](int v) {
            // change ip
            ui.label_ip->setText(ipPortString());
            networkHelper->setIpPort(ipStringLive.get(), portLive.get());
        });

        sendPlainTextLive.observe([this](QString v) {
            if (ui.plain_text_edit_send->toPlainText() != v)
                ui.plain_text_edit_send->setPlainText(v);
        });

        ipStringLive.observe([this](QString v) {
            // change ip
            ui.label_ip->setText(ipPortString());
            networkHelper->setIpPort(ipStringLive.get(), portLive.get());
        });
        receivePlainTextLive.observe([this](QString v) {
            if (ui.plain_text_edit_receive->toPlainText() != v)
                ui.plain_text_edit_receive->setPlainText(v);
        });
    }
}

TextSync::~TextSync()
{
}

void TextSync::openSetIpDialog()
{
    SetIpPortDialog dialog(this, ipStringLive.get(), portLive.get());
    dialog.setOnSubmitListener([this](QString ip, int port) {
        ipStringLive.set(ip);
        portLive.set(port);
    });
    dialog.exec();
}

void TextSync::send()
{
    // send data to server on click or timer signal
    networkHelper->post(ui.plain_text_edit_send->toPlainText());
}

void TextSync::receive()
{
    print << ipPortString().toStdString() << nl;
    networkHelper->get();
}

QString TextSync::ipPortString()
{
    return ipStringLive.get() + ":" + QString::number(portLive.get());
}
