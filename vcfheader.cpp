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


    QByteArrayList lines = mRaw.split('\n');

    for (QByteArray b_line : lines)
    {
        QString line(b_line);
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
