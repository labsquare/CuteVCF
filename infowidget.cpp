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
#include "infowidget.h"

InfoWidget::InfoWidget(VcfModel * vcfModel, QWidget *parent)
    : QWidget(parent)
{

    mModel    = new QStandardItemModel;
    mView     = new QTableView;
    mVcfModel = vcfModel;

    mModel->setColumnCount(2);
    mView->horizontalHeader()->hide();
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setModel(mModel);
    mView->verticalHeader()->setVisible(false);

    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->setAlternatingRowColors(true);
    mView->horizontalHeader()->setHighlightSections(false);

    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mView);
    cLayout->setContentsMargins(0,0,0,0);
    setLayout(cLayout);

}

void InfoWidget::setLine(const QModelIndex &index)
{
    // avoid cliping with clear... Will probably change this with custom model
    int count = mModel->rowCount();
    mModel->removeRows(0, count);
    mModel->setHorizontalHeaderLabels(QStringList()<<tr("Key")<<tr("Value"));
    mView->horizontalHeader()->show();

    VcfLine line = mVcfModel->line(index);

    QHash<QByteArray, QVariant> infos = line.infos();

    for (QByteArray key : infos.keys()){

        QStandardItem * keyItem = new QStandardItem(QString::fromUtf8(key));
        QStandardItem * valItem = new QStandardItem(infos.value(key).toString());

        keyItem->setEditable(false);
        valItem->setEditable(false);

        keyItem->setToolTip(mVcfModel->header().info(key).value("Description").toString());

        QList<QStandardItem*> row ;
        row.append(keyItem);
        row.append(valItem);

        mModel->appendRow(row);

    }

    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

}

void InfoWidget::clear()
{
    mModel->clear();
}
