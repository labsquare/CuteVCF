#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mView         = new QTableView;
    mModel        = new VcfModel;
    mSearchEdit   = new QLineEdit;
    mInfoWidget   = new InfoWidget;
    mSampleWidget = new SampleWidget;

    mView->setModel(mModel);
    setCentralWidget(mView);

    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);

    mSearchEdit->setPlaceholderText("chrX:start-end");

    QToolBar * mainToolBar = new QToolBar("main toolbar");
    addToolBar(Qt::BottomToolBarArea, mainToolBar);


    mainToolBar->addWidget(mSearchEdit);
    setFilename("/home/sacha/test.vcf.gz");

    QDockWidget * infoDock = new QDockWidget("Infos");
    infoDock->setWidget(mInfoWidget);

    QDockWidget * sampleDock = new QDockWidget("Sample");
    sampleDock->setWidget(mSampleWidget);

    addDockWidget(Qt::RightDockWidgetArea, infoDock);
    addDockWidget(Qt::RightDockWidgetArea, sampleDock);


    connect(mSearchEdit,SIGNAL(textChanged(QString)),this,SLOT(setRegion(QString)));
    connect(mView, SIGNAL(activated(QModelIndex)),this,SLOT(setInfo(QModelIndex)));

}

MainWindow::~MainWindow()
{
}

void MainWindow::setRegion(const QString &region)
{
    mModel->setRegion(region);
}

void MainWindow::setInfo(const QModelIndex &index)
{
    mInfoWidget->setLine(mModel->line(index));
    mSampleWidget->setLine(mModel->line(index));
}

void MainWindow::setFilename(const QString &filename)
{
    mModel->setFilename("/home/sacha/test.vcf.gz");
}
