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
    qDebug()<<"salt";

    for (QString key : line.infos().keys()){

        QStandardItem * keyItem = new QStandardItem(key);
        QStandardItem * valItem = new QStandardItem(line.infos().value(key).toString());

        QList<QStandardItem*> row ;
        row.append(keyItem);
        row.append(valItem);

        mModel->appendRow(row);

    }

    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

}
