#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QtWidgets>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

protected:
    void makeHeader();

private:
QTabWidget * mTabWidget;
QDialogButtonBox * mButtons;


};

#endif // ABOUTDIALOG_H
