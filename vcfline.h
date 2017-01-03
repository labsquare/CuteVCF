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

#ifndef VCFLINE_H
#define VCFLINE_H
#include <QtCore>

class VcfLine
{
public:
    VcfLine();

    static VcfLine fromLine(const QByteArray& line);

    const QByteArray& chromosom() const;
    void setChromosom(const QByteArray &chromosom);

    quint64 position() const;
    void setPosition(const quint64 &position);

    const QByteArray& id() const;
    void setId(const QByteArray &id);

    const QByteArray& ref() const;
    void setRef(const QByteArray &ref);

    const QByteArray& alt() const;
    void setAlt(const QByteArray &alt);

    int qual() const;
    void setQual(int qual);

    const QByteArray& filter() const;
    void setFilter(const QByteArray &filter);

    const QByteArray& rawFormat() const;
    QByteArrayList formats() const;
    void setRawFormat(const QByteArray &rawFormat);

    const QByteArray& rawInfos() const;
    QHash<QByteArray, QVariant> infos() const;
    void setRawInfos(const QByteArray &rawInfos);

    QByteArray rawSample(int i) const;
    QHash<QByteArray, QVariant> sample(int i);
    void addRawSample(const QByteArray& rawSample);
    int sampleCount() const;

    QString location() const;


private:
    QByteArray mChromosom;
    quint64 mPosition = 0;
    QByteArray mId;
    QByteArray mRef;
    QByteArray mAlt;
    int mQual = 0;
    QByteArray mFilter;
    QByteArray mFormat;
    QByteArray mInfos;
    QByteArrayList mSamples;

};

#endif // VCFLINE_H
