#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(tr("About"));

    mTabWidget = new QTabWidget;

    QLabel * mIconLabel = new QLabel;
    QLabel * mTitleLabel = new QLabel;

    mIconLabel->setPixmap(QPixmap(":/app.png").scaledToHeight(64, Qt::SmoothTransformation));
    mTitleLabel->setText(qApp->applicationName());
    mTitleLabel->setAlignment(Qt::AlignLeft);
    QFont font;
    font.setPixelSize(25);
    mTitleLabel->setFont(font);

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mIconLabel);
    hLayout->addWidget(mTitleLabel);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(mTabWidget);

   QPlainTextEdit * edit =  new QPlainTextEdit;
   edit->setPlainText(QString("Version: %1").arg(qApp->applicationVersion()));

  mTabWidget->addTab(edit, "Version");

    setLayout(vLayout);


}

void AboutDialog::makeHeader()
{

//    QPixmap pix(width(), height()/2);
//    pix.fill(Qt::white);

//    QPainter painter(&pix);

//    QPixmap logo = QPixmap(":/app.png");
//    int size = 128;
//    int margin = (pix.height() - size) / 2  ;

//    painter.drawPixmap(0,margin,logo);

//    QRect area(130, 0, pix.width()-130, pix.height() );

//    QFont font;
//    font.setPixelSize(30);
//    painter.setFont(font);

//    painter.drawText(area, Qt::AlignLeft|Qt::AlignVCenter, qApp->applicationName() + "\n" + qApp->applicationVersion());


//    mHeader->setPixmap(pix);
//    mHeader->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
//    mHeader->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);



}
