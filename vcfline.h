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
    void setRawFormat(const QByteArray &rawFormat);

    const QByteArray& rawInfos() const;
    QHash<QByteArray, QVariant> infos() const;
    void setRawInfos(const QByteArray &rawInfos);

    const QByteArray &rawSample(int i) const;
    void addRawSample(const QByteArray& rawSample);

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
