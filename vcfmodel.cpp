#include "vcfmodel.h"

VcfModel::VcfModel(QObject * parent):
    QAbstractListModel(parent)
{

    mBaseColors['A'] = QColor("#71E096");
    mBaseColors['C'] = QColor("#668DE5");
    mBaseColors['G'] = QColor("#4E4E56");
    mBaseColors['T'] = QColor("#ed6d79");

    connect(&mFutureWatcher, SIGNAL(finished()), this,SLOT(loaded()));

}

int VcfModel::rowCount(const QModelIndex &parent) const
{
    return mLines.count();
}

int VcfModel::columnCount(const QModelIndex &parent) const
{

    return 7;
}

QVariant VcfModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    VcfLine line = mLines.at(index.row());

    if ( role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0 : return line.chromosom();
        case 1 : return line.position();
        case 2 : return line.id();
        case 3 : return line.ref();
        case 4 : return line.alt();
        case 5 : return line.qual();
        case 6 : return line.filter();
        default : return QVariant();

        }

    }
    return QVariant();
}

QVariant VcfModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (section)
            {
            case 0 : return tr("Chromosom");
            case 1 : return tr("Position");
            case 2 : return tr("Identifier");
            case 3 : return tr("Reference");
            case 4 : return tr("Alternatif");
            case 5 : return tr("Quality");
            case 6 : return tr("Filter");
            default : return QVariant();

            }
        }
    }
    return QVariant();
}

void VcfModel::load()
{
    // this methods is called async by setRegion
    setLoading(true);
    mTampons.clear();

    QByteArray line;
    mRealCount = 0;

    if (mTabixFile.open())
    {
        while (mTabixFile.readLineInto(line))
        {
            if (mRealCount < MAX_ITEMS)
            {
                VcfLine item = VcfLine::fromLine(line) ;
                mTampons.append(item);
            }
            mRealCount++;
        }
    }


    setLoading(false);

}

void VcfModel::setLoading(bool enable)
{
    mLoading = enable;
    emit loadingChanged();
}


void VcfModel::setRegion(const QString &region)
{
    // launch async data load
    mFuture.cancel();
    mFuture.waitForFinished();
    mTabixFile.setRegion(region);
    mFuture = QtConcurrent::run(this, &VcfModel::load);
    mFutureWatcher.setFuture(mFuture);
}

QString VcfModel::filename() const
{
    return mFilename;
}

void VcfModel::setFilename(const QString &filename)
{
    mFilename = filename;
    mLines.clear();
    mTabixFile.setFilename(filename);
    mHeader.setRaw(mTabixFile.header());

}

const VcfLine &VcfModel::line(const QModelIndex &index)
{
    return mLines.at(index.row());
}

const VcfHeader &VcfModel::header() const
{
    return mHeader;
}

const QStringList &VcfModel::chromosoms() const
{
    return mTabixFile.chromosoms();
}

void VcfModel::exportCsv(const QString &filename) const
{
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);

        for (VcfLine line : mLines)
        {

            stream<<line.chromosom()<<"\t"<<line.position()<<"\t"<<line.id()<<"\t"<<line.ref()<<"\t";
            stream<<line.alt()<<"\t"<<line.qual()<<"\t"<<line.filter();
            stream<<"\n";

        }
        file.close();

    }

}

int VcfModel::count() const
{
    return mLines.count();
}

quint64 VcfModel::realCount() const
{
    return mRealCount;
}

void VcfModel::clear()
{
    mLines.clear();

}

bool VcfModel::isLoading() const
{
    return mLoading;
}

void VcfModel::loaded()
{
    // this methods is called when async load has been done
    beginResetModel();

    mLines.swap(mTampons);

    endResetModel();

}

