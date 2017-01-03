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

#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H
#include <QtWidgets>
#include "vcfline.h"
#include "vcfmodel.h"
class SampleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SampleWidget(VcfModel * vcfModel, QWidget *parent = 0);

public Q_SLOTS:
    void setLine(const QModelIndex& index);
    void clear();

protected Q_SLOTS:
    void setSample(int id);
private:
    QComboBox * mSampleBox;
    QTableView * mView;
    QStandardItemModel * mModel;
    VcfLine mCurrentLine;
    VcfModel * mVcfModel;

};

#endif // SAMPLEWIDGET_H
