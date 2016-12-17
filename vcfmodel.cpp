#include "vcfmodel.h"

VcfModel::VcfModel(QObject * parent):
    QAbstractListModel(parent)
{

    mBaseColors['A'] = QColor("#71E096");
    mBaseColors['C'] = QColor("#668DE5");
    mBaseColors['G'] = QColor("#4E4E56");
    mBaseColors['T'] = QColor("#ed6d79");

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

    if ( role == Qt::TextColorRole)
    {
        if (index.column() == 3) {
            if (line.ref().size() == 1)
                return mBaseColors.value(line.ref().at(0));
        }

        if (index.column() == 4) {
            if (line.alt().size() == 1)
                return mBaseColors.value(line.alt().at(0));
        }
    }

    if (role == Qt::FontRole && (index.column() == 3 || index.column()==4))
    {
        QFont font;
        font.setBold(true);
        return font;
    }





    if (role == Qt::DecorationRole)
    {
        if (index.column() == 0)
            return QIcon(":/dna.png");
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


void VcfModel::setRegion(const QString &region)
{
    beginResetModel();
    mLines.clear();

    mTabixFile.setRegion(region);

    QByteArray line;
    while (mTabixFile.readLineInto(line))
    {
        VcfLine item = VcfLine::fromLine(line);
        mLines.append(item);
    }

    endResetModel();
}

QString VcfModel::filename() const
{

    return mFilename;
}

bool VcfModel::setFilename(const QString &filename)
{
    mFilename = filename;
    mLines.clear();
    bool success = mTabixFile.setFilename(filename);

    if (success)
        mHeader.setRaw(mTabixFile.header());

    return success;




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

void VcfModel::clear()
{
    mLines.clear();

}
