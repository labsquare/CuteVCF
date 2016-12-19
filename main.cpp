
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTableView>
#include "vcfmodel.h"
#include <cstdarg>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("CuteVCF");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setApplicationVersion("0.1.0");



    MainWindow win;

    win.show();

    app.exec();




}
