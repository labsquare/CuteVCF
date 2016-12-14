#include "samplewidget.h"

SampleWidget::SampleWidget(QWidget *parent) : QWidget(parent)
{
    mSampleBox = new QComboBox;
    mView      = new QTableView;
    mModel     = new QStandardItemModel;

    mView->setModel(mModel);
    mModel->setColumnCount(2);

    mView->setModel(mModel);
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->setAlternatingRowColors(true);

    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mSampleBox);
    cLayout->addWidget(mView);
    cLayout->setContentsMargins(0,0,0,0);

    setLayout(cLayout);

    connect(mSampleBox,SIGNAL(activated(int)),this,SLOT(setSample(int)));

}

void SampleWidget::setLine(const VcfLine &line)
{
    mCurrentLine = line;
    mSampleBox->clear();

    for (int i=0; i<line.sampleCount(); ++i)
        mSampleBox->addItem(QString("Sample %1").arg(i));

    setSample(0);


}

void SampleWidget::setSample(int id)
{
    mModel->clear();

    QHash<QByteArray, QVariant> samples  = mCurrentLine.sample(id);

    for (QByteArray key : samples.keys()){

        QStandardItem * keyItem = new QStandardItem(QString::fromUtf8(key));
        QStandardItem * valItem = new QStandardItem(samples.value(key).toString());

        QList<QStandardItem*> row ;
        row.append(keyItem);
        row.append(valItem);

        mModel->appendRow(row);

    }
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

}
