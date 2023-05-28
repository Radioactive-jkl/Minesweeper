#include "mainwindow.h"


Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),centralget(0),mineView(0),minescene(0),minenumLcd(0),timeLcd(0),smilebtn(0),m_timer(0)
{
    this->setWindowTitle("MineSweeper");
    this->setWindowIcon(QIcon(":/images/mine.png"));
    this->create_action();
    this->create_menu();
    this->slot_newgame();
}

void Mainwindow::create_action()
{
    //Game level choices' settings
    primarleveaction = new QAction("primary",this);
    primarleveaction->setCheckable(true);

    middleleveaction = new QAction("middle",this);
    middleleveaction->setCheckable(true);

    seniorleveaction = new QAction("senior",this);
    seniorleveaction->setCheckable(true);

    customleveaction = new QAction("custom",this);
    customleveaction->setCheckable(true);

    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(primarleveaction);
    actionGroup->addAction(middleleveaction);
    actionGroup->addAction(seniorleveaction);
    actionGroup->addAction(customleveaction);
    this->connect(actionGroup,SIGNAL(triggered(QAction*)),this,SLOT(slot_newgamebyleve(QAction*)));

    rankaction = new QAction("rank",this);
    this->connect(rankaction,SIGNAL(triggered(bool)),this,SLOT(slot_rankchecked()));

    exitaction = new QAction("quit",this);
    this->connect(exitaction,SIGNAL(triggered(bool)),this,SLOT(close()));

    aboutaction = new QAction("about",this);
    this->connect(aboutaction,SIGNAL(triggered(bool)),this,SLOT(slot_about()));
}

void Mainwindow::slot_newgame()
{
    centralget->deleteLater();
    mineView->deleteLater();
    minescene->deleteLater();
    minenumLcd->deleteLater();

    timeLcd->deleteLater();
    smilebtn->deleteLater();
    m_timer->deleteLater();
    //main widget object
    centralget = new QWidget(this);

    QPalette textPalette;
    textPalette.setColor(QPalette::Normal,QPalette::WindowText,Qt::blue);
    minenumLcd = new QLCDNumber(centralget);
    minenumLcd->setPalette(textPalette);

    minenumLcd->setDigitCount(3);
    timeLcd = new QLCDNumber(centralget);
    timeLcd->setPalette(textPalette);
    timeLcd->setDigitCount(3);

    smilebtn = new QPushButton(centralget);
    smilebtn->setIcon(QPixmap(":/images/center.png"));
    this->connect(smilebtn,SIGNAL(clicked()),this,SLOT(slot_newgame()));
    QHBoxLayout *hboxlayout = new QHBoxLayout;

    hboxlayout->addWidget(minenumLcd);
    hboxlayout->addStretch();
    hboxlayout->addWidget(smilebtn);
    hboxlayout->addStretch();
    hboxlayout->addWidget(timeLcd);

    mineView = new QGraphicsView(centralget);
    minescene = new MineScene(mineView);
    mineView->setScene(minescene);
    this->readsettings();

    this->connect(minescene,SIGNAL(sig_scenenewGame()),this,SLOT(slot_newgame()));
    this->connect(minescene,SIGNAL(sig_scenedisplayMineNum(int)),this,SLOT(slot_displayMineNum(int)));
    this->connect(minescene,SIGNAL(sig_successPassGame()),this,SLOT(slot_update()));
    QVBoxLayout *vboxlayout = new QVBoxLayout(centralget);

    vboxlayout->addLayout(hboxlayout);
    vboxlayout->addWidget(mineView);
    this->setCentralWidget(centralget);
    minescene->setSceneRect(0,0,minescene->m_scenecol * COMMON::MAPWIDTH,minescene->m_scenerow * COMMON::MAPHEIGHT);
    mineView->setFixedSize(minescene->m_scenecol *COMMON::MAPWIDTH + 5,minescene->m_scenerow * COMMON::MAPHEIGHT + 5);
    this->setFixedSize(minescene->m_scenecol * COMMON::MAPWIDTH + 25,minescene->m_scenerow * COMMON::MAPHEIGHT + 75);

    if     (minescene->m_crrentleve == COMMON::PRIMARLEVE)
        primarleveaction->setChecked(true);
    else if(minescene->m_crrentleve == COMMON::MIDDLELEVE)
        middleleveaction->setChecked(true);
    else if(minescene->m_crrentleve == COMMON::SENIORLEVE)
        seniorleveaction->setChecked(true);

    m_time = 0;
    minenumLcd->display(minescene->m_minesum);
    timeLcd->display(m_time);
    m_timer = new QTimer(this);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_displayTime()));
    m_timer->start(1000);
    minescene->initscene();
}

void Mainwindow::create_menu()
{
    QMenuBar *menu_bar = this->menuBar();
    QMenu *file_menu = menu_bar->addMenu("options");
    QMenu *help_menu = menu_bar->addMenu("help");

    file_menu->addAction(primarleveaction);
    file_menu->addAction(middleleveaction);
    file_menu->addAction(seniorleveaction);
    file_menu->addAction(customleveaction);

    file_menu->addSeparator();

    file_menu->addAction(rankaction);
    file_menu->addAction(exitaction);
    help_menu->addAction(aboutaction);
}

void Mainwindow::readsettings()
{
    QSettings *setting = new QSettings("Get_arg","crr",this);
    minescene->m_scenecol = setting->value("crr_col",9).toInt();
    minescene->m_scenerow = setting->value("crr_row",9).toInt();
    minescene->m_minesum = setting->value("crr_sum",10).toInt();
    minescene->m_crrentleve = setting->value("crr_leve",0).toInt();
}

void Mainwindow::writesettings()
{
    QSettings *setting = new QSettings("Get_arg","crr",this);
    setting->setValue("crr_row" ,minescene->m_scenerow  );
    setting->setValue("crr_col" ,minescene->m_scenecol  );
    setting->setValue("crr_sum" ,minescene->m_minesum   );
    setting->setValue("crr_leve",minescene->m_crrentleve);
}

void Mainwindow::slot_newgamebyleve(QAction *act)
{
    if     (act == primarleveaction)
    {
        this->minescene->m_scenerow   = COMMON::PRIMARROWANDCOL;
        this->minescene->m_scenecol   = COMMON::PRIMARROWANDCOL;
        this->minescene->m_minesum    = COMMON::PRIMARMINNUM;
        this->minescene->m_crrentleve = COMMON::PRIMARLEVE;

    }
    else if(act == middleleveaction)
    {
        this->minescene->m_scenerow   = COMMON::MIDDLEROWANDCOL;
        this->minescene->m_scenecol   = COMMON::MIDDLEROWANDCOL;
        this->minescene->m_minesum    = COMMON::MIDDLEMINENUM;
        this->minescene->m_crrentleve = COMMON::MIDDLELEVE;

    }
    else if(act == seniorleveaction)
    {
        this->minescene->m_scenerow   = COMMON::SENIORROW;
        this->minescene->m_scenecol   = COMMON::SENIORCOL;
        this->minescene->m_minesum    = COMMON::SENIORMINENUM;
        this->minescene->m_crrentleve = COMMON::SENIORLEVE;
    }
    else if(act == customleveaction)
    {
        CustomGameDialog *custom = new CustomGameDialog(this);
        this->connect(custom,SIGNAL(signal_sendCustomset(int,int,int)),this,SLOT(slot_acceptCustomvale(int,int,int)));
        custom->exec();
    }
    this->writesettings();

    this->slot_newgame();
}

void Mainwindow::slot_acceptCustomvale(int rownum,int colnum,int minenum)
{
    minescene->m_crrentleve = COMMON::CUSTOMLEVE;
    minescene->m_scenecol = rownum;
    minescene->m_scenerow = colnum;
    minescene->m_minesum = minenum;

    //save current game
    this->writesettings();
    this->slot_newgame();
}

void Mainwindow::slot_rankchecked()
{
    rank *ranklist = new rank(this);
    ranklist->exec();
}

void Mainwindow::slot_about()
{
    QString str = tr("Game: MineSweeper\n Version: 1.1\n Author:Radioactive-jkl\n");
    QMessageBox::about(this,tr("Some Information"),str);
}

void Mainwindow::slot_update()
{
    QSettings settings("Get_arg","rank");
    int recordtime = 999;
    QString newname;
    switch(minescene->m_crrentleve)
    {
        case 0:
            recordtime = settings.value("primartime").toInt();
            qDebug("%d",recordtime);
            if(m_time < recordtime)
            {
                bool ok;
                newname = QInputDialog::getText(
                            this,
                            tr("NEW RECORD"),
                            "A new record came out! Please enter your name:",
                            QLineEdit::Normal,QString(),
                            &ok
                            );
                if(ok)
                {
                    settings.setValue("primartime",m_time);
                    settings.setValue("primarname",newname);
                }
            }
            break;

        case 1:
            recordtime = settings.value("middletime").toInt();
            if(m_time < recordtime)
            {
                bool ok;
                newname = QInputDialog::getText(
                            this,
                            tr("NEW RECORD"),
                            "A new record came out! Please enter your name:",
                            QLineEdit::Normal,QString(),
                            &ok
                            );
                if(ok)
                {
                    settings.setValue("middletime",m_time);
                    settings.setValue("middlename",newname);
                }
            }
            break;

        case 2:
            recordtime = settings.value("seniortime").toInt();
            if(m_time < recordtime)
            {
                bool ok;
                newname = QInputDialog::getText(
                            this,
                            tr("NEW RECORD"),
                            "A new record came out! Please enter your name:",
                            QLineEdit::Normal,QString(),
                            &ok
                            );
                if(ok)
                {
                    settings.setValue("seniortime",m_time);
                    settings.setValue("seniorname",newname);
                }
            }
            break;

    }

    QString speech = "Succeed in ";
    speech = speech + QString::number(m_time) + " seconds!\n Go on?";
    QMessageBox button(QMessageBox::Question,"Game Over",speech,QMessageBox::Ok | QMessageBox::No,NULL);

    if(button.exec() == QMessageBox::Ok)
        slot_newgame();
    else
        this->close();
}

void Mainwindow::slot_displayMineNum(int flagminenum)
{
    if((minescene->m_minesum - flagminenum) >= 0)
    minenumLcd->display(minescene->m_minesum - flagminenum);
}

void Mainwindow::slot_displayTime()
{
    if(!minescene->m_isGameover)
    {
        m_time++;

        timeLcd->display(m_time);
    }
    else
    {
        m_timer->stop();
    }
}

Mainwindow::~Mainwindow()
{

}
