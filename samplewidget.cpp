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
#include "samplewidget.h"

SampleWidget::SampleWidget(VcfModel * vcfModel,QWidget *parent) : QWidget(parent)
{
    mSampleBox = new QComboBox;
    mView      = new QTableView;
    mModel     = new QStandardItemModel;
    mVcfModel  = vcfModel;

    mView->setModel(mModel);
    mModel->setColumnCount(2);

    mView->setModel(mModel);
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->hide();
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->horizontalHeader()->setHighlightSections(false);

    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mSampleBox);
    cLayout->addWidget(mView);
    cLayout->setContentsMargins(0,0,0,0);

    setLayout(cLayout);

    connect(mSampleBox,SIGNAL(activated(int)),this,SLOT(setSample(int)));

}

void SampleWidget::setLine(const QModelIndex &index)
{
    mCurrentLine = mVcfModel->line(index);
    mSampleBox->clear();

    QStringList colnames =  mVcfModel->header().colnames();

    for (int i=9; i<colnames.count(); ++i)
        mSampleBox->addItem(colnames.at(i));

    setSample(0);

}

void SampleWidget::setSample(int id)
{
    mModel->clear();

    mView->horizontalHeader()->show();
    mModel->setHorizontalHeaderLabels(QStringList()<<tr("Key")<<tr("Value"));

    qDebug()<<mCurrentLine.sample(0);

    QHash<QByteArray, QVariant> samples  = mCurrentLine.sample(id);
    for (QByteArray key : samples.keys()){

        QStandardItem * keyItem = new QStandardItem(QString::fromUtf8(key));
        QStandardItem * valItem = new QStandardItem(samples.value(key).toString());

        keyItem->setEditable(false);
        valItem->setEditable(false);

        keyItem->setToolTip(mVcfModel->header().format(key).value("Description").toString());

        QList<QStandardItem*> row ;
        row.append(keyItem);
        row.append(valItem);

        mModel->appendRow(row);

    }
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

}

void SampleWidget::clear()
{
    mModel->clear();
}
