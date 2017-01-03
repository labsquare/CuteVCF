/*
This file is part of CuteVCF.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

@author : Sacha Schutz <sacha@labsquare.org>
*/

#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(tr("About"));

    mTabWidget = new QTabWidget;

    QLabel * mIconLabel = new QLabel;
    QLabel * mTitleLabel = new QLabel;


    mCancelButton = new QPushButton(tr("Cancel"));
    mGithubButton = new QPushButton(tr("Github"));

    mIconLabel->setPixmap(QPixmap(":icons/app.png").scaledToHeight(64, Qt::SmoothTransformation));
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
