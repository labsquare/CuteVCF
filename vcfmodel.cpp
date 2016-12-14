#include "vcfmodel.h"

VcfModel::VcfModel(QObject * parent):
    QAbstractListModel(parent)
{

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

    if ( role == Qt::DisplayRole)
    {

        VcfLine line = mLines.at(index.row());

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
        if (role == Qt::DisplayRole)
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

void VcfModel::setRegion(const QString &region)
{
    beginResetModel();
    mLines.clear();

    string s_region(region.toStdString());
    mTabixFile.setRegion(s_region);
    string line;
    while (mTabixFile.getNextLine(line))
    {
        VcfLine item = VcfLine::fromLine(QByteArray::fromStdString(line));
        mLines.append(item);
    }


    endResetModel();
}

QString VcfModel::filename() const
{

    return mFilename;
}

void VcfModel::setFilename(const QString &filename)
{
    mFilename = filename;

    string s_filename = mFilename.toStdString();
    mTabixFile.setFilename(s_filename);

}

const VcfLine &VcfModel::line(const QModelIndex &index)
{
    return mLines.at(index.row());
}
