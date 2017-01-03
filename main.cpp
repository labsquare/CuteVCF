/*
This file is part of CuteVCF.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

@author : Sacha Schutz <sacha@labsquare.org>
*/

#include <QApplication>
#include <QDebug>
#include <QTableView>

#include "mainwindow.h"
#include "qfonticon.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("CuteVCF");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setApplicationVersion("0.2.0");



    if (!QFontIcon::addFont(":/fonts/fontawesome.ttf"))
        qCritical()<<"Cannot add font";



    MainWindow win;

    win.show();

    app.exec();




}
