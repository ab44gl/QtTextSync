#include "stdafx.h"
#include "QtTextSync.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTextSync w;
    w.show();
    return a.exec();
}
