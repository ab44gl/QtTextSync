#include "stdafx.h"
#include "QtTextSync.h"
#include <QtWidgets/QApplication>
#include "LayoutWindow.h"
#include "LiveDataWindow.h"
#include"TextSync.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextSync w;
    w.show();
    return a.exec();
    //send-receive
}
