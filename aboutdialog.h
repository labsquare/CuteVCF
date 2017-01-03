#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QtWidgets>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

public Q_SLOTS:
    void openGithub();

protected:
    void appendTab(const QString& filename, const QString& label);


private:
QTabWidget * mTabWidget;
QDialogButtonBox * mButtons;

QPushButton * mCancelButton;
QPushButton * mGithubButton;


};

#endif // ABOUTDIALOG_H
