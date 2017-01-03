/*
This file is part of CuteVCF.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

@author : Sacha Schutz <sacha@labsquare.org>
*/
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

}

void QTabix::setRegion(const QString &region)
{
    mRegions = region;
}

const QString &QTabix::region() const
{
    return mRegions;
}

const QString &QTabix::filename() const
{
    return mFilename;
}

void QTabix::setFilename(const QString &filename)
{
    mFilename = filename;
    if (QFile::exists(mFilename))
        readInfo();
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


    tbx_itr_destroy(iter);
    tbx_destroy(tbx);

    return false;

}
void QTabix::buildIndex(const QString &filename)
{
    // build vcf.gz.tbi
    tbx_conf_t conf = tbx_conf_vcf;
    int min_shift = 0;
    tbx_index_build(filename.toStdString().c_str(), min_shift, &conf);
}

bool QTabix::open()
{
    fp   = NULL;
    tbx  = NULL;
    iter = NULL;
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

    tbx->conf = tbx_conf_vcf;
    str= {0,0,0};

    // set region
    iter = tbx_itr_querys(tbx, mRegions.toStdString().c_str());

    if (!iter){
        qCritical()<<"could not query the region "<<mRegions;
        return false;
    }
    return true;
}


bool QTabix::readInfo()
{

    fp   = NULL;
    tbx  = NULL;
    iter = NULL;
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
        if ( !str.l || str.s[0]!=tbx->conf.meta_char ) {
            break;
        }
        else {
            mHeaders.append(str.s);
            mHeaders.append('\n');
        }

    }

    tbx_itr_destroy(iter);
    tbx_destroy(tbx);

}



