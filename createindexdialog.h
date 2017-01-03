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

#ifndef CREATEINDEXDIALOG_H
#define CREATEINDEXDIALOG_H
#include <QtWidgets>
#include <QtConcurrent>
#include "qtabix.h"
class CreateIndexDialog : public QProgressDialog
{
    Q_OBJECT
public:
    CreateIndexDialog(const QString& filename, QWidget * parent = 0);
    int exec() Q_DECL_OVERRIDE;

protected Q_SLOTS:
    void cancelIndexBuilding();
    void finishIndexBuilding();


private:
    QString mFilename;
    QFuture<void> mFuture;
    QFutureWatcher<void> mWatcher;
};

#endif // CREATEINDEXDIALOG_H
