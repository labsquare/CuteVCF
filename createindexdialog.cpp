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
#include "createindexdialog.h"

CreateIndexDialog::CreateIndexDialog(const QString& filename,QWidget *parent)
    :QProgressDialog(parent)
{
    mFilename = filename;

    setMinimum(0);
    setMaximum(0);

    setLabelText(tr("Creating index, please wait ..."));

    connect(this,SIGNAL(canceled()), this, SLOT(cancelIndexBuilding()));
    connect(&mWatcher,SIGNAL(finished()),this,SLOT(finishIndexBuilding()));

}

int CreateIndexDialog::exec()
{

    mFuture = QtConcurrent::run(&QTabix::buildIndex, mFilename);
    mWatcher.setFuture(mFuture);
    return QProgressDialog::exec();

}

void CreateIndexDialog::cancelIndexBuilding()
{
    mFuture.cancel();
    QFile::remove(QString("%1.tbi").arg(mFilename));
    reject();
}

void CreateIndexDialog::finishIndexBuilding()
{
    setLabelText(tr("Creating index done!"));
    setMaximum(100);
    setValue(100);
    accept();
}

