/*
This file is part of CuteVCF.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

@author : Sacha Schutz <sacha@labsquare.org>
*/
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
    mLoadingLabel = new QLabel(this);
    mLoadingAnimation = new QMovie(":icons/squares.gif");
    mChromBox     = new QComboBox;


    setWindowIcon(QIcon(":icons/app.png"));

    // set the main table view properties
    mView->setModel(mModel);
    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->setHighlightSections(false);
    mView->setContextMenuPolicy(Qt::CustomContextMenu);

    // set the searchbar properties
    mSearchEdit->setPlaceholderText(tr("Select a region... <chr> or <chr:start-end>"));
    mSearchEdit->setCompleter(new QCompleter);
    mSearchEdit->completer()->setCaseSensitivity(Qt::CaseInsensitive);
    QAction * searchAction = mSearchEdit->addAction(QFontIcon::icon(0xf002),QLineEdit::TrailingPosition);


    mLoadingLabel->setMovie(mLoadingAnimation);
    mLoadingAnimation->jumpToNextFrame();

    // mSearchEdit is inside a QtoolBar
    mMainToolBar = new QToolBar("main toolbar");
    mMainToolBar->setFloatable(false);
    mMainToolBar->setAllowedAreas(Qt::TopToolBarArea);
    mMainToolBar->setMovable(false);
    mMainToolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);

    mMainToolBar->addWidget(mChromBox);
    mMainToolBar->addWidget(mSearchEdit);
    mMainToolBar->addWidget(mLoadingLabel);


    addToolBar(Qt::TopToolBarArea, mMainToolBar);






    // Create info Dock
    mInfoDock = new QDockWidget(tr("Infos fields"));
    mInfoDock->setWidget(mInfoWidget);
    mInfoDock->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::RightDockWidgetArea, mInfoDock);

    // Create Sample Dock
    mSampleDock= new QDockWidget(tr("Sample fields"));
    mSampleDock->setWidget(mSampleWidget);
    mSampleDock->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::RightDockWidgetArea, mSampleDock);

    connect(mSearchEdit,SIGNAL(returnPressed()),this,SLOT(loadRegion()));
    connect(searchAction,SIGNAL(triggered(bool)),this,SLOT(loadRegion()));
    connect(mView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mInfoWidget,SLOT(setLine(QModelIndex)));
    connect(mView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mSampleWidget,SLOT(setLine(QModelIndex)));
    connect(mModel,SIGNAL(loadingChanged()),this,SLOT(loadingChanged()));
    connect(mView, SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onVariantContextMenu(QPoint)));
    connect(mChromBox,SIGNAL(currentIndexChanged(int)),this,SLOT(chromboxChanged()));

    createMenuBar();
    statusBar()->addPermanentWidget(mVariantCount);


    setCentralWidget(mView);



    resize(800,600);

    //    setStyleSheet("QMainWindow::separator{margin:0px;padding:0px; width:3px}");
    //   setStyleSheet("QDockWidget::title{margin:0px;}");
    //   setStyleSheet("QTableView{margin:0px;}");
    //   setStyleSheet("QDockWidget{margin:0px;}");

    //   setStyleSheet("QTableView::item { border-left: 0px }");

}

MainWindow::~MainWindow()
{
    delete mView;
    delete mModel;
    delete mSearchEdit;
    delete mInfoWidget;
    delete mSampleWidget;
    delete mInfoDock;
    delete mSampleDock;
    delete mVariantCount;
}

void MainWindow::loadRegion()
{

    QString region = mSearchEdit->text();

    // this methodes is asynchronious ..
    mModel->setRegion(region);
}



void MainWindow::setFilename(const QString &filename)
{
    if (filename.isEmpty())
        return;

    // if index doesn't exists, create it
    if (!QFile::exists(filename+QString(".tbi"))){

        int ret = QMessageBox::question(this,tr("index is missing"),tr("Index file doesn't exist. Would you like to create it ?"));
        if (ret == QMessageBox::Yes)
        {
            CreateIndexDialog dialog(filename,this);
            if ( dialog.exec() == QDialog::Rejected)
                return;
        }
        else
            return;
    }

    // set model with filename and reset the view.

    if ( QFile::exists(filename))
    {
        mModel->setFilename(filename);
        addRecent(filename);

        reset();
        if (!mModel->chromosoms().isEmpty()){
            mSearchEdit->completer()->setModel(new QStringListModel(mModel->chromosoms()));
            mChromBox->setModel(new QStringListModel(mModel->chromosoms()));

            // by defaut, set to the chromosom 1
            //            mSearchEdit->setText(mModel->chromosoms().last());

            loadRegion();

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

void MainWindow::focusRegionEdit()
{
    // focus on region edit ! This is called by the shortcut Ctrl + F
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

void MainWindow::showRawHeader()
{

    // show a simple dialog of raw headers
    QDialog * dialog = new QDialog;
    QPlainTextEdit * mEdit = new QPlainTextEdit(dialog);
    mEdit->setReadOnly(true);
    QVBoxLayout * vLayout = new QVBoxLayout;
    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    vLayout->addWidget(mEdit);
    vLayout->addWidget(buttonBox);
    dialog->setLayout(vLayout);

    QObject::connect(buttonBox,SIGNAL(rejected()),dialog,SLOT(close()));
    mEdit->setPlainText(mModel->header().raw());
    dialog->resize(600,400);
    dialog->setWindowTitle(tr("Raw header"));
    dialog->exec();
    delete dialog;



}

void MainWindow::showInfo()
{
    // show a simple dialog of raw headers
    QDialog * dialog = new QDialog;
    QVBoxLayout * dLayout  = new QVBoxLayout(dialog);
    QTabWidget * tabWidget = new QTabWidget(dialog);
    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);

    dLayout->addWidget(tabWidget);
    dLayout->addWidget(buttonBox);
    dialog->setLayout(dLayout);

    QObject::connect(buttonBox,SIGNAL(rejected()),dialog,SLOT(close()));
    QTreeWidget * tagsView = new QTreeWidget(dialog);
    tagsView->setColumnCount(2);
    tagsView->setHeaderLabels(QStringList()<<"Key"<<"Value");
    for (QString key : mModel->header().tags().keys())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setText(0, key);
        item->setText(1, mModel->header().tags().value(key).toString());
        tagsView->addTopLevelItem(item);
    }


    tagsView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tabWidget->addTab(tagsView, tr("Tags"));
    dialog->setWindowTitle(tr("Information"));

    dialog->resize(500,500);
    dialog->exec();



    delete dialog;

}


void MainWindow::setVariantCount(int count)
{
    if (count == 0)
        mVariantCount->setText(QString());
    else
        mVariantCount->setText(QString("Total: %1").arg(mModel->count()));
}

void MainWindow::reset()
{
    mInfoWidget->clear();
    mSampleWidget->clear();
    mModel->clear();
    mSearchEdit->clear();
}

void MainWindow::addRecent(const QString &filename)
{
    QSettings settings;
    QStringList paths = loadRecent();

    // Don't save if it already exists
    if (paths.contains(filename))
        return;

    paths.append(filename);

    // 30 maximum file in recent menu
    if (paths.size() > 30)
        paths.removeFirst();

    settings.beginWriteArray("recent");
    int i = 0;

    for (QString path : paths)
    {
        settings.setArrayIndex(i);
        settings.setValue("path", path);
        ++i;
    }

    settings.endArray();



}

QStringList MainWindow::loadRecent()
{
    QSettings settings;
    QStringList paths;
    int size = settings.beginReadArray("recent");

    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString filename = settings.value("path").toString();
        if (QFile::exists(filename))
            paths.append(filename);
    }
    settings.endArray();

    return paths;


}

void MainWindow::createMenuBar()
{
    QMenuBar * bar = new QMenuBar;

    // File menu
    QMenu * fileMenu = bar->addMenu(tr("&File"));
    fileMenu->addAction(QFontIcon::icon(0xf115), tr("&Open of vcf file"),this,SLOT(openFile()),QKeySequence::Open);

    QMenu * recentFile = new QMenu(tr("&Recent files"));
    for (QString recent : loadRecent())
        recentFile->addAction(recent,this,SLOT(recentClicked()));

    fileMenu->addMenu(recentFile);


    fileMenu->addAction(QFontIcon::icon(0xf0c7),tr("&Export to CSV"),this,SLOT(exportCsv()),QKeySequence::Save);
    fileMenu->addAction(QFontIcon::icon(0xf08b),tr("&Quit"),qApp, SLOT(closeAllWindows()), QKeySequence::Quit);



    // Edit menu
    QMenu * editMenu = bar->addMenu(tr("&Edit"));
    editMenu->addAction(QFontIcon::icon(0xf002),tr("Set region ..."), this, SLOT(focusRegionEdit()), QKeySequence::Find);


    // Window menu
    QMenu * viewMenu = bar->addMenu(tr("&Window"));
    QAction * infoAction = viewMenu->addAction(tr("Show Info fields"),mInfoDock,SLOT(setVisible(bool)));
    infoAction->setCheckable(true);
    infoAction->setChecked(true);

    QAction * sampleAction = viewMenu->addAction(tr("Show sample fields"),mSampleDock,SLOT(setVisible(bool)));
    sampleAction->setCheckable(true);
    sampleAction->setChecked(true);

    viewMenu->addSeparator();
    viewMenu->addAction(QFontIcon::icon(0xf06e),tr("Show raw header"),this, SLOT(showRawHeader()));
    viewMenu->addAction(QFontIcon::icon(0xf06e),tr("Show information"),this, SLOT(showInfo()));



    // Help menu
    QMenu * helpMenu = bar->addMenu(tr("&Help"));
    helpMenu->addAction(QFontIcon::icon(0xf129),tr("About %1").arg(qApp->applicationName()),this,SLOT(showAbout()));
    helpMenu->addAction(QFontIcon::icon(0xf129),tr("About Qt"),qApp,SLOT(aboutQt()));


    setMenuBar(bar);


    //    QWidget * empty = new QWidget;
    //    empty->setMinimumWidth(50);
    //    empty->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    //    mMainToolBar->addWidget(empty);




}

void MainWindow::loadingChanged()
{

    bool enable = mModel->isLoading();

    if (enable){
        mLoadingAnimation->start();
    }
    else{
        mLoadingAnimation->stop();
        mVariantCount->setText(QString("Total: %1").arg(mModel->realCount()));

    }

    mView->setDisabled(enable);
    mInfoDock->setDisabled(enable);
    mSampleDock->setDisabled(enable);
    mSearchEdit->setDisabled(enable);
}

void MainWindow::onVariantContextMenu(const QPoint &pos)
{
    // show a context menu when right click on a variant

    qDebug()<<"click";
    QMenu variantMenu;

    QAction * ucsc    = variantMenu.addAction(QIcon(":/ucsc.png"),tr("Open with UCSC"));
    QAction * ensembl = variantMenu.addAction(QIcon(":/ensembl.png"),tr("Open with Ensembl"));
    QAction * copyLoc = variantMenu.addAction(tr("Copy location"));


    QModelIndex index =mView->indexAt(pos);
    QAction * rep = nullptr;


    if (index.isValid())
        rep = variantMenu.exec(mView->mapToGlobal(pos));
    else
        return;

    if (rep == copyLoc)
    {
        QApplication::clipboard()->setText(mModel->line(index).location());
        return;
    }


    QString url;
    if (rep == ucsc)
        url = QString("http://genome.ucsc.edu/cgi-bin/hgTracks?org=%1&db=%2&position=%3").arg("human").arg("hg19").arg(mModel->line(index).location());


    if (rep == ensembl)
        url = QString("http:/www.ensembl.org/%1/Location/View?r=%2").arg("human").arg(mModel->line(index).location());



    QDesktopServices::openUrl(QUrl(url));

}

void MainWindow::recentClicked()
{
    QAction * action = qobject_cast<QAction*>(sender());

    if (action)
        setFilename(action->text());

}

void MainWindow::chromboxChanged()
{

    mSearchEdit->setText(mChromBox->currentText());
    loadRegion();

}
