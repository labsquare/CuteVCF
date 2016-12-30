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
