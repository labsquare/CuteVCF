#include "infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent)
{

    mModel = new QStandardItemModel;
    mView  = new QTableView;

    mModel->setColumnCount(2);

    mView->setModel(mModel);
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->setAlternatingRowColors(true);
    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mView);
    cLayout->setContentsMargins(0,0,0,0);
    setLayout(cLayout);

}

void InfoWidget::setLine(const VcfLine &line)
{
    mModel->clear();

    QHash<QByteArray, QVariant> infos = line.infos();

    for (QByteArray key : infos.keys()){

        QStandardItem * keyItem = new QStandardItem(QString::fromUtf8(key));
        QStandardItem * valItem = new QStandardItem(infos.value(key).toString());

        QList<QStandardItem*> row ;
        row.append(keyItem);
        row.append(valItem);

        mModel->appendRow(row);

    }

    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

}
