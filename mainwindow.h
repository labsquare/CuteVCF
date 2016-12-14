#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "vcfmodel.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setRegion(const QString& region);

private:
    QTableView * mView;
    VcfModel * mModel;
    QLineEdit * mSearchEdit;


};

#endif // MAINWINDOW_H
