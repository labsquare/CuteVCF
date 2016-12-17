#include "qtabix.h"

QTabix::QTabix()
{

}

QTabix::QTabix(const QString &filename)
{
    setFilename(filename);
}

bool QTabix::setRegion(const QString &region)
{
    if (!tbx)
        return false;

    mRegions = region;
    tbx_itr_destroy(iter);
    iter = tbx_itr_querys(tbx, region.toStdString().c_str());
    has_jumped = true;
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
    mFilename  = filename;
    mChromosoms.clear();
    mHeaders.clear();
    has_jumped = false;
    // Open file
    fn = hts_open(mFilename.toStdString().c_str(),"r");
    if (fn == NULL){
        qCritical()<<Q_FUNC_INFO<<"cannot open file "<<filename;
        return false;
    }

    // Open index
    tbx = tbx_index_load(mFilename.toStdString().c_str());

    if (tbx == NULL) {
        qCritical()<<Q_FUNC_INFO<<"cannot open file "<<filename;
        return false;
    }

    int nseq;
    const char** seq = tbx_seqnames(tbx, &nseq);
    for (int i=0; i<nseq; i++) {
        mChromosoms.append(seq[i]);
    }

    delete seq;
    idxconf = &tbx_conf_vcf;

    //seek 0
    iter = tbx_itr_querys(tbx, mChromosoms.first().toStdString().c_str());

    readHeader();
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
    line.clear();
    kstring_t str;
    str.l = 0;
    str.m = 0;
    str.s = NULL;

    auto current_chrom  = mChromosoms.begin();

    if (has_jumped) {
        if (iter && tbx_itr_next(fn, tbx, iter, &str) >= 0) {
            line = QByteArray(str.s);
            return true;
        } else return false;
    } else { // step through all sequences in the file
        // we've never jumped, so read everything
        if (iter && tbx_itr_next(fn, tbx, iter, &str) >= 0) {
            line = QByteArray(str.s);
            return true;
        } else {
            ++current_chrom;
            while (current_chrom != mChromosoms.end()) {
                tbx_itr_destroy(iter);
                iter = tbx_itr_querys(tbx, current_chrom->toStdString().c_str());
                if (iter && tbx_itr_next(fn, tbx, iter, &str) >= 0) {
                    line = QByteArray(str.s);
                    return true;
                } else {
                    ++current_chrom;
                }
            }
            return false;
        }
    }
    return false;
}

void QTabix::buildIndex(const QString &filename)
{
    tbx_conf_t conf = tbx_conf_vcf;
    int min_shift = 0;
    tbx_index_build(filename.toStdString().c_str(), min_shift, &conf);
}

void QTabix::readHeader()
{
    mHeaders.clear();

    if ( fn == nullptr || tbx == nullptr)
        qWarning()<<"No file loaded";

    tbx_itr_querys(tbx, mChromosoms.first().toStdString().c_str());

    kstring_t str;
    str.l = 0;
    str.m = 0;
    str.s = NULL;

    while ( hts_getline(fn, KS_SEP_LINE, &str) >= 0 ) {

        if ( !str.l || str.s[0]!=tbx->conf.meta_char ) {
            break;
        } else {
            mHeaders.append(str.s);
            mHeaders.append('\n');
        }
    }

    iter = tbx_itr_querys(tbx, mChromosoms.first().toStdString().c_str());
}
