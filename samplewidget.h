#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H
#include <QtWidgets>
#include "vcfline.h"
#include "vcfmodel.h"
class SampleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SampleWidget(VcfModel * vcfModel, QWidget *parent = 0);

public Q_SLOTS:
    void setLine(const QModelIndex& index);
    void clear();

protected Q_SLOTS:
    void setSample(int id);
private:
    QComboBox * mSampleBox;
    QTableView * mView;
    QStandardItemModel * mModel;
    VcfLine mCurrentLine;
    VcfModel * mVcfModel;

};

#endif // SAMPLEWIDGET_H
