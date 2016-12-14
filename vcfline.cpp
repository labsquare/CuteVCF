#include "vcfline.h"

VcfLine::VcfLine()
{

}

QString VcfLine::chromosom() const
{
    return mChromosom;
}

void VcfLine::setChromosom(const QString &chromosom)
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

QString VcfLine::id() const
{
    return mId;
}

void VcfLine::setId(const QString &id)
{
    mId = id;
}

QString VcfLine::ref() const
{
    return mRef;
}

void VcfLine::setRef(const QString &ref)
{
    mRef = ref;
}

QString VcfLine::alt() const
{
    return mAlt;
}

void VcfLine::setAlt(const QString &alt)
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

QString VcfLine::filter() const
{
    return mFilter;
}

void VcfLine::setFilter(const QString &filter)
{
    mFilter = filter;
}

void VcfLine::addInfo(const QString &key, const QVariant &value)
{
    mInfos[key] = value;
}



void VcfLine::clearInfo()
{
    mInfos.clear();
}

void VcfLine::addSampleInfo(const QString &sample, const QString &key, const QVariant &value)
{
    if (!mSamples.contains(sample))
        mSamples.insert(sample, QHash<QString, QVariant>());

    else
        mSamples[sample][key] = value;
}

void VcfLine::clearSample()
{
    mSamples.clear();
}
