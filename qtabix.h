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
    ~QTabix();

    void setRegion(const QString& region);
    const QString& region() const;


    const QString& filename() const;
    void setFilename(const QString &filename);

    const QByteArray& header() const;
    const QStringList& chromosoms() const;

    bool readLineInto(QByteArray& line);

    static void buildIndex(const QString& filename);

    bool open();




protected:
    bool readInfo();

private:
    QString mFilename;
    QStringList mChromosoms;
    QByteArray mHeaders;
    QString mRegions;
    htsFile* fp     = NULL;
    tbx_t* tbx      = NULL;
    hts_itr_t* iter = NULL;
    kstring_t str;


};

#endif // QTABIX_H
