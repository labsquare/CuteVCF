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
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->setAlternatingRowColors(true);
    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mView);
    cLayout->setContentsMargins(0,0,0,0);
    setLayout(cLayout);

}

void InfoWidget::setLine(const QModelIndex &index)
{
    mModel->clear();
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
