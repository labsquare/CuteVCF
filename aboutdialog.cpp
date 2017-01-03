#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(tr("About"));

    mTabWidget = new QTabWidget;

    QLabel * mIconLabel = new QLabel;
    QLabel * mTitleLabel = new QLabel;


    mCancelButton = new QPushButton(tr("Cancel"));
    mGithubButton = new QPushButton(tr("Github"));

    mIconLabel->setPixmap(QPixmap(":/app.png").scaledToHeight(64, Qt::SmoothTransformation));
    mIconLabel->setFixedWidth(64);
    mTitleLabel->setText(qApp->applicationName()+" "+qApp->applicationVersion());
    mTitleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QFont font;
    font.setPixelSize(25);
    mTitleLabel->setFont(font);

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mIconLabel);
    hLayout->addWidget(mTitleLabel);
    hLayout->setAlignment(mTitleLabel,Qt::AlignLeft);

    QHBoxLayout * bLayout = new QHBoxLayout;
    bLayout->addWidget(mGithubButton);
    bLayout->addStretch();
    bLayout->addWidget(mCancelButton);


    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(mTabWidget);
    vLayout->addLayout(bLayout);


    setLayout(vLayout);
    setFixedSize(500,500);

    appendTab(":README", tr("About"));
    appendTab(":CHANGELOG", tr("Version"));
    appendTab(":LICENSE", tr("License"));
    appendTab(":AUTHORS", tr("Authors"));


    connect(mCancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(mGithubButton,SIGNAL(clicked(bool)),this,SLOT(openGithub()));


}

void AboutDialog::openGithub()
{
    QDesktopServices::openUrl(QUrl("http://github.com/labsquare/CuteVCF"));

}

void AboutDialog::appendTab(const QString &filename, const QString &label)
{

    QFile file(filename);
    if (file.open(QIODevice::Text|QIODevice::ReadOnly))
    {
       QPlainTextEdit * edit = new QPlainTextEdit;
       mTabWidget->addTab(edit, label);
       edit->setPlainText(file.readAll());
    }
}
