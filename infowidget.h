#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QtWidgets>
#include <QTableView>
#include <QStandardItemModel>
#include "vcfline.h"
class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QWidget *parent = 0);

    void setLine(const VcfLine& line);

private:
    QStandardItemModel * mModel;
    QTableView * mView;
};

#endif // INFOWIDGET_H
