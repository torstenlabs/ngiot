#include "ngiot.h"
#include <QtCore>
#include <QtGlobal>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ngiot w;
    w.show();

    return a.exec();
}
