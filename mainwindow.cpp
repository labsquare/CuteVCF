#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mView       = new QTableView;
    mModel      = new VcfModel;
    mSearchEdit = new QLineEdit;

    mView->setModel(mModel);
    setCentralWidget(mView);

    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);

    mSearchEdit->setPlaceholderText("chrX:start-end");

    QToolBar * mainToolBar = new QToolBar("main toolbar");
    addToolBar(Qt::BottomToolBarArea, mainToolBar);


    mainToolBar->addWidget(mSearchEdit);


    mModel->setFilename("/home/sacha/test.vcf.gz");

    connect(mSearchEdit,SIGNAL(textChanged(QString)),this,SLOT(setRegion(QString)));

}

MainWindow::~MainWindow()
{
}

void MainWindow::setRegion(const QString &region)
{
    mModel->setRegion(region);
}
