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

#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QtWidgets>
#include <QTableView>
#include <QStandardItemModel>
#include "vcfline.h"
#include "vcfmodel.h"
class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(VcfModel * vcfModel, QWidget *parent = 0);
public Q_SLOTS:
    void setLine(const QModelIndex& index);
    void clear();

private:
    QStandardItemModel * mModel;
    QTableView * mView;
    VcfModel * mVcfModel;
};

#endif // INFOWIDGET_H
