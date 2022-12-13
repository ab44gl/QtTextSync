#pragma once

#include <QMainWindow>
#include "ui_LiveDataWindow.h"
#include "stdafx.h"

class LiveDataWindow : public QMainWindow
{
    Q_OBJECT

  public:
    LiveDataWindow(QWidget *parent = nullptr);
    ~LiveDataWindow();

  private:
    Ui::LiveDataWindowClass ui;
    LiveData<int> count = 50;
    LiveData<QString> msgString = "";
    LiveData<QString> plainMsgString = "";
    LiveData<int> isOn = Qt::Checked;
};
