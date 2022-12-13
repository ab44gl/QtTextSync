#include "stdafx.h"
#include "QtTextSync.h"
#include <QtWidgets/QApplication>
#include "LayoutWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LayoutWindow w;
    w.show();
    return a.exec();
    //send-receive
}
