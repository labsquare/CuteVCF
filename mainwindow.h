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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "vcfmodel.h"
#include "infowidget.h"
#include "samplewidget.h"
#include "aboutdialog.h"
#include "createindexdialog.h"
#include "qfonticon.h"

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
    void chromboxChanged();

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
    QLabel * mLoadingLabel;
    QMovie * mLoadingAnimation;
    QComboBox * mChromBox;



};

#endif // MAINWINDOW_H
