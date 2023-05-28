#include "rank.h"


// UI design in Constructor
rank::rank(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Rank");
    QLabel *label1 = new QLabel(tr("primary:"));
    QLabel *label2 = new QLabel(tr("middle :"));
    QLabel *label3 = new QLabel(tr("senior :"));

    primarrecordnamelabel = new QLabel;
    primarrecordtimelabel = new QLabel;
    middlerecordnamelabel = new QLabel;
    middlerecordtimelabel = new QLabel;
    seniorrecordnamelabel = new QLabel;
    seniorrecordtimelabel = new QLabel;

    QGridLayout *glayout = new QGridLayout(this);

    glayout->addWidget(label1,0,0);
    glayout->addWidget(primarrecordtimelabel,0,1);
    glayout->addWidget(primarrecordnamelabel,0,2);
    glayout->addWidget(label2,1,0);

    glayout->addWidget(middlerecordtimelabel,1,1);
    glayout->addWidget(middlerecordnamelabel,1,2);
    glayout->addWidget(label3,2,0);
    glayout->addWidget(seniorrecordtimelabel,2,1);
    glayout->addWidget(seniorrecordnamelabel,2,2);

    QPushButton *reset = new QPushButton("reset");
    this->connect(reset,SIGNAL(clicked()),this,SLOT(slot_reset()));
    QPushButton *confirm = new QPushButton("confirm");
    this->connect(confirm,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(reset);
    hlayout->addWidget(confirm);
    hlayout->addStretch();
    glayout->addLayout(hlayout,3,0,2,2);
    this->readsettings();
}

void rank::readsettings()
{
    QSettings *ranksetting = new QSettings("Get_arg","rank",this);
    int primartime = ranksetting->value("primartime", 999).toInt();
    int middletime = ranksetting->value("middletime", 999).toInt();
    int seniortime = ranksetting->value("seniortime", 999).toInt();

    QString primarname = ranksetting->value("primarname", "---").toString();
    QString middlename = ranksetting->value("middlename", "---").toString();
    QString seniorname = ranksetting->value("seniorname", "---").toString();

    primarrecordtimelabel->setNum (primartime);
    middlerecordtimelabel->setNum (middletime);
    seniorrecordtimelabel->setNum (seniortime);
    primarrecordnamelabel->setText(primarname);
    middlerecordnamelabel->setText(middlename);
    seniorrecordnamelabel->setText(seniorname);
}

void rank::inti_rankrecord()
{
    QSettings *writesetting = new QSettings("Get_arg","rank",this);
    writesetting->setValue("primartime", 999);
    writesetting->setValue("middletime", 999);
    writesetting->setValue("seniortime", 999);

    writesetting->setValue("primarname", "---");
    writesetting->setValue("middlename", "---");
    writesetting->setValue("seniorname", "---");
}

void rank::slot_reset()
{
    this->inti_rankrecord();
    this->readsettings();
}
