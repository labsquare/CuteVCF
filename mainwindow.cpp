#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mView         = new QTableView;
    mModel        = new VcfModel;
    mSearchEdit   = new QLineEdit;
    mInfoWidget   = new InfoWidget(mModel);
    mSampleWidget = new SampleWidget(mModel);

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
    connect(mView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mInfoWidget,SLOT(setLine(QModelIndex)));
    connect(mView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mSampleWidget,SLOT(setLine(QModelIndex)));

}

MainWindow::~MainWindow()
{
}

void MainWindow::setRegion(const QString &region)
{
    mModel->setRegion(region);
}



void MainWindow::setFilename(const QString &filename)
{
    mModel->setFilename("/home/sacha/test.vcf.gz");
}
