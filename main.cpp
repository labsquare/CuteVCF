
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTableView>
#include "vcfmodel.h"
#include <cstdarg>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);




        MainWindow win;

        win.show();

    app.exec();




}
