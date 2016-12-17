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

    bool setRegion(const QString& region);
    const QString& region() const;


    const QString& filename() const;
    bool setFilename(const QString &filename);

    const QByteArray& header() const;
    const QStringList& chromosoms() const;

    bool readLineInto(QByteArray& line);


protected:
    void readHeader();

private:
    QString mFilename;
    QStringList mChromosoms;
    QByteArray mHeaders;
    QString mRegions;
    htsFile* fn = nullptr;
    tbx_t* tbx  = nullptr;
    hts_itr_t* iter =nullptr;
    bool has_jumped;
    const tbx_conf_t *idxconf;


};

#endif // QTABIX_H
