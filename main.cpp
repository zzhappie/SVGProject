#include "mainwindow.h"
#include "kglobaldata.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    KGlobalData::getGlobalDataIntance()->loadButtonTips();
    MainWindow w;
    w.show();
    return a.exec();
}
