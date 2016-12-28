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


protected:
    void createMenuBar();
    void setVariantCount(int count);
    void reset();


protected Q_SLOTS:
    void loadingChanged();

private:
    QTableView * mView;
    VcfModel * mModel;
    QLineEdit * mSearchEdit;
    InfoWidget * mInfoWidget;
    SampleWidget * mSampleWidget;

    QDockWidget * mInfoDock;
    QDockWidget * mSampleDock;
    QLabel * mVariantCount;
    QMovie * mLoadingAnimation;



};

#endif // MAINWINDOW_H
