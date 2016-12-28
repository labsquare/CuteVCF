#include "createindexdialog.h"

CreateIndexDialog::CreateIndexDialog(const QString& filename,QWidget *parent)
    :QProgressDialog(parent)
{
    mFilename = filename;

    setMinimum(0);
    setMaximum(0);

    setLabelText(tr("Creating index, please wait ..."));

    connect(this,SIGNAL(canceled()), this, SLOT(cancelIndexBuilding()));
    connect(&mWatcher,SIGNAL(finished()),this,SLOT(finishIndexBuilding()));

}

int CreateIndexDialog::exec()
{

    mFuture = QtConcurrent::run(&QTabix::buildIndex, mFilename);
    mWatcher.setFuture(mFuture);
    return QProgressDialog::exec();

}

void CreateIndexDialog::cancelIndexBuilding()
{
    mFuture.cancel();
    QFile::remove(QString("%1.tbi").arg(mFilename));
    reject();
}

void CreateIndexDialog::finishIndexBuilding()
{
    setLabelText(tr("Creating index done!"));
    setMaximum(100);
    setValue(100);
    accept();
}

