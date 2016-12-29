#ifndef VCFMODEL_H
#define VCFMODEL_H
#include <QtCore>
#include <QIcon>
#include <QFont>
#include <QtConcurrent>
#include "vcfline.h"
#include "vcfheader.h"
#include "qtabix.h"

#define MAX_ITEMS 100000

using namespace  std;

class VcfModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ isLoading WRITE setLoading NOTIFY loadingChanged)
public:

    VcfModel(QObject * parent = Q_NULLPTR);

    void setRegion(const QString& region);
    QString filename() const;
    void setFilename(const QString &filename);
    const VcfLine& line(const QModelIndex& index);

    const VcfHeader& header() const;
    const QStringList& chromosoms() const;

    void exportCsv(const QString& filename) const;
    int count() const;
    quint64 realCount() const;

    void clear();

    bool isLoading() const;

Q_SIGNALS:
    void loadingChanged();


protected Q_SLOTS:
    void loaded();

protected:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    void load();
    void setLoading(bool enable);

private:
    QVector<VcfLine> mLines;
    QVector<VcfLine> mTampons;

    VcfHeader mHeader;
    QString mFilename;
    QTabix mTabixFile;
    QHash<char, QColor> mBaseColors;
    QString mRegion;
    QFuture<void> mFuture;
    QFutureWatcher<void> mFutureWatcher;
    bool mLoading;
    quint64 mRealCount;



};

#endif // VCFMODEL_H
