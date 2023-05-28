/* * * * * * * * * * * * * * * *
 * --------Mainwindow--------  *
 *                             *
 *  @ UI design by QT lins     *
 *              instead of .ui *
 *  @ separate front end       *
 *      with interaction logic *
 * * * * * * * * * * * * * * * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QGraphicsView>
#include <QLCDNumber>
#include <QPushButton>
#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>
#include <QPalette>
#include <QTimer>
#include <QMessageBox>
#include <QInputDialog>

#include "common.h"
#include "customgamedialog.h"
#include "minescene.h"
#include "rank.h"


class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

    //action objects for menu
    QAction *primarleveaction;
    QAction *middleleveaction;
    QAction *seniorleveaction;
    QAction *customleveaction;
    QAction *rankaction;
    QAction *exitaction;
    QAction *aboutaction;

    //objects in mainwindow
    QWidget *centralget;
    QGraphicsView *mineView;
    MineScene *minescene;
    QLCDNumber *minenumLcd;
    QLCDNumber *timeLcd;
    QPushButton *smilebtn;
    int m_time;
    QTimer *m_timer;

public slots:
    //functions: feedback of actions
    void create_action();
    void create_menu();
    void readsettings();
    void writesettings();
    void slot_newgame();
    void slot_acceptCustomvale(int,int,int);
    void slot_rankchecked();
    void slot_about();
    void slot_update();
    void slot_displayMineNum(int);
    void slot_displayTime();
    void slot_newgamebyleve(QAction*);
};



#endif // MAINWINDOW_H
