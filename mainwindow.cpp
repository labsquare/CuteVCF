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

    mSearchEdit->setPlaceholderText(tr("Write the region to select in format <chr> or <chr:start-end>"));
    mSearchEdit->setCompleter(new QCompleter);
    mSearchEdit->completer()->setCaseSensitivity(Qt::CaseInsensitive);



    QToolBar * mainToolBar = new QToolBar("main toolbar");
    addToolBar(Qt::BottomToolBarArea, mainToolBar);


    mainToolBar->addWidget(mSearchEdit);

    mInfoDock = new QDockWidget(tr("Infos fields"));
    mInfoDock->setWidget(mInfoWidget);
    mInfoDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);

    mSampleDock= new QDockWidget(tr("Sample fields"));
    mSampleDock->setWidget(mSampleWidget);
    mSampleDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::RightDockWidgetArea, mInfoDock);
    addDockWidget(Qt::RightDockWidgetArea, mSampleDock);


    connect(mSearchEdit,SIGNAL(textChanged(QString)),this,SLOT(setRegion(QString)));
    connect(mView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mInfoWidget,SLOT(setLine(QModelIndex)));
    connect(mView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mSampleWidget,SLOT(setLine(QModelIndex)));


    createMenuBar();

    resize(800,600);



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
    mInfoWidget->clear();
    mSampleWidget->clear();
    mModel->clear();
    mSearchEdit->clear();

    mModel->setFilename(filename);
    mSearchEdit->completer()->setModel(new QStringListModel(mModel->chromosoms()));

    if (!mModel->chromosoms().isEmpty()){
        mSearchEdit->setText(mModel->chromosoms().first());
        setRegion(mModel->chromosoms().first());
    }
    else
        qWarning()<<Q_FUNC_INFO<<"Cannot find chromosoms";
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Vcf file"), QDir::homePath(), tr("Vcf Files (*.vcf.gz)"));
    setFilename(fileName);
}

void MainWindow::createMenuBar()
{
    QMenuBar * bar = new QMenuBar;

    // File menu
    QMenu * fileMenu = bar->addMenu(tr("&File"));
    fileMenu->addAction(tr("Open of vcf file"),this,SLOT(openFile()),QKeySequence::Open);
    fileMenu->addAction(tr("Close"),qApp, SLOT(closeAllWindows()), QKeySequence::Quit);

    // Edit menu
    QMenu * editMenu = bar->addMenu(tr("&Edit"));
    editMenu->addAction(tr("Set region ..."), mSearchEdit, SLOT(selectAll()), QKeySequence::Find);


    // Window menu
    QMenu * viewMenu = bar->addMenu(tr("&Window"));
    QAction * infoAction = viewMenu->addAction(tr("Show Info fields"),mInfoDock,SLOT(setVisible(bool)));
    infoAction->setCheckable(true);
    infoAction->setChecked(true);

    QAction * sampleAction = viewMenu->addAction(tr("Show sample fields"),mSampleDock,SLOT(setVisible(bool)));
    sampleAction->setCheckable(true);
    sampleAction->setChecked(true);

    // Help menu
    QMenu * helpMenu = bar->addMenu(tr("&Help"));
    helpMenu->addAction(tr("About Qt"),qApp,SLOT(aboutQt()));


    setMenuBar(bar);

}
