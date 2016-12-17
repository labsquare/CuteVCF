#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "vcfmodel.h"
#include "infowidget.h"
#include "samplewidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void setRegion(const QString& region);
    void setFilename(const QString& filename);
    void openFile();
    void searchRegion();
    void exportCsv();

protected:
    void createMenuBar();

private:
    QTableView * mView;
    VcfModel * mModel;
    QLineEdit * mSearchEdit;
    InfoWidget * mInfoWidget;
    SampleWidget * mSampleWidget;

     QDockWidget * mInfoDock;
     QDockWidget * mSampleDock;


};

#endif // MAINWINDOW_H
