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

#ifndef VCFHEADER_H
#define VCFHEADER_H
#include <QtCore>

class VcfHeader
{
public:
    VcfHeader();
    VcfHeader(const QByteArray& raw);

    void setRaw(const QByteArray& raw);
    const QByteArray& raw() const;

    QHash<QString, QVariant> info(const QString& key) const;
    QHash<QString, QVariant> format(const QString& key) const;
    const QHash<QString, QVariant>& tags() const;
    const QStringList& colnames() const;


protected:
    static QHash<QString, QVariant> captureParams(const QString& line);


private:
    QByteArray mRaw;
    QHash<QString, QHash<QString, QVariant>> mInfos;
    QHash<QString, QHash<QString, QVariant>> mFormats;
    QHash<QString, QVariant> mTags;

    QStringList mColnames;
};

#endif // VCFHEADER_H
