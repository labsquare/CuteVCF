#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mView = new QTableView;
    mModel = new VcfModel;

    mView->setModel(mModel);
    setCentralWidget(mView);

    mModel->setFilename("/home/sacha/test.vcf.gz");

    mModel->setRegion("chr6:1-1000000");
}

MainWindow::~MainWindow()
{
}
