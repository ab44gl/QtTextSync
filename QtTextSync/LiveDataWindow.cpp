#include "stdafx.h"
#include "LiveDataWindow.h"

LiveDataWindow::LiveDataWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    Event::SpinBoxValueChanged(ui.spinbox_count, [this](int v) { count.set(v); });

    count.observe([this](int data) {
        ui.spinbox_count->setValue(data);
        // label
        ui.label_count->setText(QString::number(data));
    });
    msgString.observe([this](QString data) {
        ui.line_edit_msg->setText(data);
        ui.label_line_edit_msg->setText(data);
    });
    plainMsgString.observe([this](QString data) {
        if (ui.plainTextEdit_msg->toPlainText() != data)
        {
            ui.plainTextEdit_msg->setPlainText(data);
        }
        ui.label_plain_text_msg->setText(data);
    });
    isOn.observe([this](int data) {
        ui.check_box_onoff->setCheckState((Qt::CheckState)data);
        ui.check_box_onoff->setText(data ? "on" : "off");
    });
    Event::ButtonClicked(ui.push_button_click_me, [this]() { std::cout << "button clicked\n"; });
    Event::LineEditTextChanged(ui.line_edit_msg, [this](QString value) { msgString.set(value); });
    Event::PlainEditTextChanged(ui.plainTextEdit_msg, [this](QString value) { plainMsgString.set(value); });
    Event::CheckBoxStateChanged(ui.check_box_onoff, [this](int value) { isOn.set(value); });
}

LiveDataWindow::~LiveDataWindow()
{
}
