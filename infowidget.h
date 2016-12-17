#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QtWidgets>
#include <QTableView>
#include <QStandardItemModel>
#include "vcfline.h"
#include "vcfmodel.h"
class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(VcfModel * vcfModel, QWidget *parent = 0);
public Q_SLOTS:
    void setLine(const QModelIndex& index);

private:
    QStandardItemModel * mModel;
    QTableView * mView;
    VcfModel * mVcfModel;
};

#endif // INFOWIDGET_H
