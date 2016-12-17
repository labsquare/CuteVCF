#ifndef VCFMODEL_H
#define VCFMODEL_H
#include <QtCore>
#include <QIcon>
#include <QFont>
#include "vcfline.h"
#include "vcfheader.h"
#include "qtabix.h"
using namespace  std;

class VcfModel : public QAbstractListModel
{
public:

    VcfModel(QObject * parent = Q_NULLPTR);

    void setRegion(const QString& region);
    QString filename() const;
    bool setFilename(const QString &filename);
    const VcfLine& line(const QModelIndex& index);

    const VcfHeader& header() const;
    const QStringList& chromosoms() const;

    void exportCsv(const QString& filename) const;
    int count() const;

    void clear();


protected:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;


private:
    QList<VcfLine> mLines;
    VcfHeader mHeader;
    QString mFilename;
    QTabix mTabixFile;
    QHash<char, QColor> mBaseColors;



};

#endif // VCFMODEL_H
