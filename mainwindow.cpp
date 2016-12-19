#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mView         = new QTableView;
    mModel        = new VcfModel;
    mSearchEdit   = new QLineEdit;
    mInfoWidget   = new InfoWidget(mModel);
    mSampleWidget = new SampleWidget(mModel);
    mVariantCount = new QLabel(this);

    setWindowIcon(QIcon(":/app.png"));

    mView->setModel(mModel);
    setCentralWidget(mView);

    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);

    mSearchEdit->setPlaceholderText(tr("Write the region to select in format <chr> or <chr:start-end>"));
    mSearchEdit->setCompleter(new QCompleter);
    mSearchEdit->completer()->setCaseSensitivity(Qt::CaseInsensitive);
    mSearchEdit->addAction(QIcon::fromTheme("system-search"),QLineEdit::LeadingPosition);
    statusBar()->addPermanentWidget(mVariantCount);



    QToolBar * mainToolBar = new QToolBar("main toolbar");
    mainToolBar->setFloatable(false);
    mainToolBar->setAllowedAreas(Qt::TopToolBarArea);
    mainToolBar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, mainToolBar);


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

    if (mModel->count() == 0)
        mVariantCount->setText(QString());
    else

        mVariantCount->setText(QString("Total: %1").arg(mModel->count()));
}



void MainWindow::setFilename(const QString &filename)
{
    if (filename.isEmpty())
        return;


    if (!QFile::exists(filename+QString(".tbi"))){

        int ret = QMessageBox::question(this,tr("index is missing"),tr("Index file doesn't exist. Would you like to create it ?"));
        if (ret == QMessageBox::Yes)
        {
            QTabix::buildIndex(filename);
        }

        else
            return;

    }



    if (mModel->setFilename(filename))
    {

        mInfoWidget->clear();
        mSampleWidget->clear();
        mModel->clear();
        mSearchEdit->clear();

        mSearchEdit->completer()->setModel(new QStringListModel(mModel->chromosoms()));
        if (!mModel->chromosoms().isEmpty()){
            mSearchEdit->setText(mModel->chromosoms().first());
            setRegion(mModel->chromosoms().first());

            statusBar()->showMessage(QString("%1 loaded").arg(filename));
            QFileInfo info(filename);
            setWindowTitle(info.fileName());
        }
    }
    else
    {
        QMessageBox::warning(this,tr("cannot open"),"Cannot open the file");
    }


}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Vcf file"), QDir::homePath(), tr("Vcf Files (*.vcf.gz)"));
    setFilename(fileName);

}

void MainWindow::searchRegion()
{
    mSearchEdit->selectAll();
    mSearchEdit->setFocus();
}

void MainWindow::exportCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Vcf file"), QDir::homePath(), tr("Csv file(*.csv)"));
    mModel->exportCsv(fileName);

}

void MainWindow::showAbout()
{
    AboutDialog dialog;
    dialog.exec();
}


void MainWindow::createMenuBar()
{
    QMenuBar * bar = new QMenuBar;

    // File menu
    QMenu * fileMenu = bar->addMenu(tr("&File"));
    fileMenu->addAction(QIcon::fromTheme("document-open"), tr("Open of vcf file"),this,SLOT(openFile()),QKeySequence::Open);
    fileMenu->addAction(QIcon::fromTheme("document-save-as"),tr("Export to CSV"),this,SLOT(exportCsv()),QKeySequence::Save);
    fileMenu->addAction(QIcon::fromTheme("application-exit"),tr("Close"),qApp, SLOT(closeAllWindows()), QKeySequence::Quit);

    // Edit menu
    QMenu * editMenu = bar->addMenu(tr("&Edit"));
    editMenu->addAction(tr("Set region ..."), this, SLOT(searchRegion()), QKeySequence::Find);


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
    helpMenu->addAction(QIcon::fromTheme("help-about"),tr("About %1").arg(qApp->applicationName()),this,SLOT(showAbout()));
    helpMenu->addAction(QIcon::fromTheme("help-about"),tr("About Qt"),qApp,SLOT(aboutQt()));


    setMenuBar(bar);

}
