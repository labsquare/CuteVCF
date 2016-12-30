#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "vcfmodel.h"
#include "infowidget.h"
#include "samplewidget.h"
#include "aboutdialog.h"
#include "createindexdialog.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void loadRegion();
    void setFilename(const QString& filename);
    void openFile();
    void focusRegionEdit();
    void exportCsv();
    void showAbout();
    void showRawHeader();
    void showInfo();


protected:
    void createMenuBar();
    void setVariantCount(int count);
    void reset();
    void addRecent(const QString& filename);
    QStringList loadRecent();


protected Q_SLOTS:
    void loadingChanged();
    void onVariantContextMenu(const QPoint& pos);
    void recentClicked();

private:
    QTableView * mView;
    VcfModel * mModel;
    QLineEdit * mSearchEdit;
    InfoWidget * mInfoWidget;
    SampleWidget * mSampleWidget;
    QToolBar * mMainToolBar;

    QDockWidget * mInfoDock;
    QDockWidget * mSampleDock;
    QLabel * mVariantCount;
    QMovie * mLoadingAnimation;



};

#endif // MAINWINDOW_H
