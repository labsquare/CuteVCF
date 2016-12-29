#include "vcfline.h"

VcfLine::VcfLine()
{
    mChromosom="chr3";
    mPosition = 10;
}

VcfLine VcfLine::fromLine(const QByteArray &line)
{

    VcfLine out;
    QByteArrayList lines = line.split(QChar::Tabulation);


    if ( line.count() >= 9)
    {

        out.setChromosom(lines.at(0));
        out.setPosition(lines.at(1).toUInt());
        out.setId(lines.at(2));
        out.setRef(lines.at(3));
        out.setAlt(lines.at(4));
        out.setQual(lines.at(5).toInt());
        out.setFilter(lines.at(6));
        out.setRawInfos(lines.at(7));
        out.setRawFormat(lines.value(8));

        for (int i=9; i<lines.count(); ++i)
            out.addRawSample(lines.at(i));

    }

    return out;
}

const QByteArray& VcfLine::chromosom() const
{
    return mChromosom;
}

void VcfLine::setChromosom(const QByteArray &chromosom)
{
    mChromosom = chromosom;
}

quint64 VcfLine::position() const
{
    return mPosition;
}

void VcfLine::setPosition(const quint64 &position)
{
    mPosition = position;
}

const QByteArray& VcfLine::id() const
{
    return mId;
}

void VcfLine::setId(const QByteArray &id)
{
    mId = id;
}

const QByteArray& VcfLine::ref() const
{
    return mRef;
}

void VcfLine::setRef(const QByteArray &ref)
{
    mRef = ref;
}

const QByteArray& VcfLine::alt() const
{
    return mAlt;
}

void VcfLine::setAlt(const QByteArray &alt)
{
    mAlt = alt;
}

int VcfLine::qual() const
{
    return mQual;
}

void VcfLine::setQual(int qual)
{
    mQual = qual;
}

const QByteArray& VcfLine::filter() const
{
    return mFilter;
}

void VcfLine::setFilter(const QByteArray &filter)
{
    mFilter = filter;
}

const QByteArray& VcfLine::rawFormat() const
{
    return mFormat;
}

QByteArrayList VcfLine::formats() const
{
    return rawFormat().split(':');
}

void VcfLine::setRawFormat(const QByteArray &format)
{
    mFormat = format;
}

const QByteArray& VcfLine::rawInfos() const
{
    return mInfos;
}

QHash<QByteArray, QVariant> VcfLine::infos() const
{
    QHash<QByteArray, QVariant> out;
    for (QByteArray item : rawInfos().split(';'))
    {
        QByteArrayList duo = item.split('=');
        if (duo.size() == 2)
            out[duo.at(0)] = duo.at(1);
    }

    return out;
}

void VcfLine::setRawInfos(const QByteArray &infos)
{
    mInfos = infos;
}

QByteArray VcfLine::rawSample(int i) const
{
    return mSamples.value(i,QByteArray());
}

QHash<QByteArray, QVariant> VcfLine::sample(int i)
{
    QHash<QByteArray, QVariant> out;
    QByteArrayList format = formats();

    qDebug()<<rawSample(i);

    QByteArrayList values = rawSample(i).split(':');
    for (int i=0; i<values.size();++i)
    {
        if (i<format.count())
        {
            out.insert(format.at(i), values.at(i));
        }

    }
    return out;
}

void VcfLine::addRawSample(const QByteArray &sample)
{
    mSamples.append(sample);
}

int VcfLine::sampleCount() const
{
    return mSamples.count();
}

QString VcfLine::location() const
{

    QString c = mChromosom;
    QString p = QString::number(mPosition);

    return c+":"+p;

}


