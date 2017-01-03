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

#ifndef QTABIX_H
#define QTABIX_H

#include <QtCore>
#include "htslib/bgzf.h"
#include "htslib/tbx.h"
#include "htslib/kseq.h"

class QTabix
{
public:
    explicit QTabix();
    explicit QTabix(const QString& filename);
    ~QTabix();

    void setRegion(const QString& region);
    const QString& region() const;


    const QString& filename() const;
    void setFilename(const QString &filename);

    const QByteArray& header() const;
    const QStringList& chromosoms() const;

    bool readLineInto(QByteArray& line);

    static void buildIndex(const QString& filename);

    bool open();




protected:
    bool readInfo();

private:
    QString mFilename;
    QStringList mChromosoms;
    QByteArray mHeaders;
    QString mRegions;
    htsFile* fp     = NULL;
    tbx_t* tbx      = NULL;
    hts_itr_t* iter = NULL;
    kstring_t str;


};

#endif // QTABIX_H
