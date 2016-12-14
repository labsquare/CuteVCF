#ifndef VCFLINE_H
#define VCFLINE_H
#include <QtCore>

class VcfLine
{
public:
    VcfLine();

    QString chromosom() const;
    void setChromosom(const QString &chromosom);

    quint64 position() const;
    void setPosition(const quint64 &position);

    QString id() const;
    void setId(const QString &id);

    QString ref() const;
    void setRef(const QString &ref);

    QString alt() const;
    void setAlt(const QString &alt);

    int qual() const;
    void setQual(int qual);

    QString filter() const;
    void setFilter(const QString &filter);

    void addInfo(const QString& key, const QVariant& value);
    void clearInfo();

    void addSampleInfo(const QString& sample, const QString& key, const QVariant& value);
    void clearSample();

private:
    QString mChromosom;
    quint64 mPosition;
    QString mId;
    QString mRef;
    QString mAlt;
    int mQual;
    QString mFilter;
    QHash<QString,QVariant> mInfos;
    QHash<QString, QHash<QString, QVariant> > mSamples;

};

#endif // VCFLINE_H
