#ifndef CREATEINDEXDIALOG_H
#define CREATEINDEXDIALOG_H
#include <QtWidgets>
#include <QtConcurrent>
#include "qtabix.h"
class CreateIndexDialog : public QProgressDialog
{
    Q_OBJECT
public:
    CreateIndexDialog(const QString& filename, QWidget * parent = 0);
    int exec() Q_DECL_OVERRIDE;

protected Q_SLOTS:
    void cancelIndexBuilding();
    void finishIndexBuilding();


private:
    QString mFilename;
    QFuture<void> mFuture;
    QFutureWatcher<void> mWatcher;
};

#endif // CREATEINDEXDIALOG_H
