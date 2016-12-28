#include "qtabix.h"

QTabix::QTabix()
{

}

QTabix::QTabix(const QString &filename)
{
    setFilename(filename);
}

QTabix::~QTabix()
{
    if (tbx)
        tbx_destroy(tbx);
}

bool QTabix::setRegion(const QString &region)
{
    if (!tbx)
        return false;

    mRegions = region;

    if (iter)
        tbx_itr_destroy(iter);

    iter = tbx_itr_querys(tbx, region.toStdString().c_str());

    if (!iter){
        qCritical()<<"could not query the region "<<region;
        return false;
    }
    return true;

}

const QString &QTabix::region() const
{
    return mRegions;
}

const QString &QTabix::filename() const
{
    return mFilename;
}

bool QTabix::setFilename(const QString &filename)
{
    mFilename = filename;
    fp  = NULL;
    tbx = NULL;
    // open file
    fp = hts_open(mFilename.toStdString().c_str(),"r");
    if (!fp){
        qCritical()<<Q_FUNC_INFO<<"Could not read "<<mFilename;
        return false;
    }
    // open index
    tbx = tbx_index_load(mFilename.toStdString().c_str());
    if (!tbx){
        qCritical()<<Q_FUNC_INFO<<"Could not read .tbi index of "<<mFilename;
        return false;
    }

    // reads chromosomes
    int nseq;
    const char **seq = NULL;
    seq = tbx_seqnames(tbx, &nseq);
    mChromosoms.clear();
    for (int i=0; i<nseq; ++i)
        mChromosoms.append(seq[i]);
    delete seq;

    // reads headers
    str= {0,0,0};
    while ( hts_getline(fp, KS_SEP_LINE, &str) >= 0 )
    {
        if ( !str.l || str.s[0]!=tbx->conf.meta_char ) break;
        mHeaders = str.s;
    }

    tbx->conf = tbx_conf_vcf;
    str= {0,0,0};

    return true;


}

const QByteArray &QTabix::header() const
{
    return mHeaders;
}

const QStringList &QTabix::chromosoms() const
{
    return mChromosoms;
}

bool QTabix::readLineInto(QByteArray &line)
{
    if (tbx_itr_next(fp, tbx, iter,&str) >= 0)
    {
        line = QByteArray(str.s);
        return true;
    }

    return false;

    //    hts_close(fp);

    //    line.clear();
    //    kstring_t str;
    //    str.l = 0;
    //    str.m = 0;
    //    str.s = NULL;

    //    auto current_chrom  = mChromosoms.begin();

    //    if (has_jumped) {
    //        if (iter && tbx_itr_next(fp, tbx, iter, &str) >= 0) {
    //            line = QByteArray(str.s);
    //            return true;
    //        } else return false;
    //    } else { // step through all sequences in the file
    //        // we've never jumped, so read everything
    //        if (iter && tbx_itr_next(fp, tbx, iter, &str) >= 0) {
    //            line = QByteArray(str.s);
    //            return true;
    //        } else {
    //            ++current_chrom;
    //            while (current_chrom != mChromosoms.end()) {
    //                tbx_itr_destroy(iter);
    //                iter = tbx_itr_querys(tbx, current_chrom->toStdString().c_str());
    //                if (iter && tbx_itr_next(fp, tbx, iter, &str) >= 0) {
    //                    line = QByteArray(str.s);
    //                    return true;
    //                } else {
    //                    ++current_chrom;
    //                }
    //            }
    //            return false;
    //        }
    //    }
    //    return false;
}

void QTabix::buildIndex(const QString &filename)
{
    tbx_conf_t conf = tbx_conf_vcf;
    int min_shift = 0;
    tbx_index_build(filename.toStdString().c_str(), min_shift, &conf);
}


