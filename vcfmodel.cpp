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


    string s_filename = mFilename.toStdString();
    Tabix file(s_filename);



    string s_region(region.toStdString());
    file.setRegion(s_region);
    string line;
    while (file.getNextLine(line))
    {
        QStringList items = QString::fromStdString(line).split("\t");
        VcfLine item;

        item.setChromosom(items.at(0));
        item.setPosition(items.at(1).toUInt());
        item.setId(items.at(2));
        item.setRef(items.at(3));
        item.setAlt(items.at(4));
        item.setQual(items.at(5).toInt());
        item.setFilter(items.at(6));

        QString info = items.at(7);
        for (QString i : info.split(";"))
        {
            QStringList ipair = i.split("=");
            if (ipair.size() == 2 )
            {
               QString key = ipair[0];
               QString val = ipair[1];
               item.addInfo(key,val);
            }

        }
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
}

const VcfLine &VcfModel::line(const QModelIndex &index)
{
    return mLines.at(index.row());
}
