#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H
#include <QtWidgets>
#include "vcfline.h"
class SampleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SampleWidget(QWidget *parent = 0);

    void setLine(const VcfLine& line);

protected Q_SLOTS:
    void setSample(int id);
private:
    QComboBox * mSampleBox;
    QTableView * mView;
    QStandardItemModel * mModel;
    VcfLine mCurrentLine;

};

#endif // SAMPLEWIDGET_H
