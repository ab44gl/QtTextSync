#pragma once

#include <QMainWindow>
#include "ui_LayoutWindow.h"
#include "NetworkHelper.h"

class LayoutWindow : public QMainWindow
{
    Q_OBJECT

  public:
    LayoutWindow(QWidget *parent = nullptr);
    ~LayoutWindow();

  private:
    Ui::LayoutWindowClass ui;
    NetworkHelper *_networkHelper = nullptr;
};
