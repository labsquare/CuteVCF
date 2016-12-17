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

public slots:
    void setRegion(const QString& region);
    void setFilename(const QString& filename);

private:
    QTableView * mView;
    VcfModel * mModel;
    QLineEdit * mSearchEdit;
    InfoWidget * mInfoWidget;
    SampleWidget * mSampleWidget;

};

#endif // MAINWINDOW_H
