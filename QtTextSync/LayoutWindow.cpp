#include "stdafx.h"
#include "LayoutWindow.h"


LayoutWindow::LayoutWindow(QWidget *parent) : QMainWindow(parent)

{
    ui.setupUi(this);
    _networkHelper = new NetworkHelper(this);
    _networkHelper->setIpPort("www.google.com", 30);
    _networkHelper->setOnMessageListener(
        [this](NetworkHelper::Message msg) { std::cout << msg.toString().toStdString() << std::endl; });
    //_networkHelper->get();
   
}

LayoutWindow::~LayoutWindow()
{
}
