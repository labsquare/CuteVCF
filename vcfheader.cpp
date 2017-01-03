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
#include "vcfheader.h"

VcfHeader::VcfHeader()
{

}

VcfHeader::VcfHeader(const QByteArray &raw)
{
    setRaw(raw);
}



void VcfHeader::setRaw(const QByteArray &raw)
{
    mRaw = raw;
    mInfos.clear();
    mFormats.clear();
    mColnames.clear();
    mTags.clear();


    QByteArrayList lines = mRaw.split('\n');

    for (QByteArray b_line : lines)
    {
        QString line(b_line);

        if (line.contains(QRegularExpression("^##[a-zA-Z0-9]+=[^<]"))){

            QStringList lines = line.split("=");
            QString key       = lines.at(0);
            QString value     = lines.at(1);
            mTags.insert(key.replace("##",""), value);

        }


        if (line.startsWith("##INFO")){
            QHash<QString, QVariant> info = captureParams(line);
            QString id = info.value("ID","unknown").toString();
            mInfos[id] = info;
        }

        if (line.startsWith("##FORMAT")){
            QHash<QString, QVariant> format = captureParams(line);
            QString id = format.value("ID","unknown").toString();
            mFormats[id] = format;
        }

        if (line.startsWith("#CHROM")){
            mColnames = line.split("\t");
        }
    }

}

const QByteArray &VcfHeader::raw() const
{
    return mRaw;
}

QHash<QString, QVariant> VcfHeader::info(const QString &key) const
{
    return mInfos.value(key);
}

QHash<QString, QVariant> VcfHeader::format(const QString &key) const
{
    return mFormats.value(key);
}

const QHash<QString, QVariant> &VcfHeader::tags() const
{
    return mTags;
}

const QStringList &VcfHeader::colnames() const
{
    return mColnames;
}

QHash<QString, QVariant> VcfHeader::captureParams(const QString &line)
{
    QString src = line;
    QHash<QString, QVariant> output;
    // Remove < and > at begin and end
    src = src.remove(QRegularExpression("^##\\w+=<")).remove(QRegularExpression(">$"));

    //capture key and value
    QRegularExpression re("([A-Za-z_0-9]+)=\"?([^,=<>\"]+)\"?");

    QRegularExpressionMatchIterator i = re.globalMatch(src);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (match.capturedTexts().count() == 3)
        {
            QString key = match.captured(1);
            QString val = match.captured(2);
            output.insert(key, val);
        }
    }

    return output;


}
