#include "mineitem.h"
#include "minescene.h"
#include "mainwindow.h"


//Parent: a single cell, picture item
MineItem::MineItem(int t_x,int t_y,QPixmap pixmap,QGraphicsItem *parent):QGraphicsPixmapItem(pixmap,parent),m_X(t_x),m_Y(t_y)
{
    m_isMine = 0;
    m_isOpened = 0;
    m_aroundMineNum = 0;
    m_rMouseKeyNum = 0;
    m_isrightMouse = false;
}

void MineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // <1> check game state after pressing the mouse
    MineScene *minescene = (MineScene *)this->scene();
    if(minescene->m_isGameover || this->m_isOpened)
    {
        return;
    }

    // <2> still in game, pressing makes sense
    if(event->button() == Qt::LeftButton && !m_isrightMouse)
    {
        this->setPixmap(QPixmap(":/images/mine1.png"));
    }
    else if(event->button() == Qt::RightButton)
    {
        m_rMouseKeyNum++;
        if(1 == m_rMouseKeyNum)
        {
        m_isrightMouse = true;
        minescene->m_signalMineNum++;
        this->setPixmap(QPixmap(":/images/flag1.png"));
        emit sig_resetMineNum(minescene->m_signalMineNum);

        if(this->m_isMine)
            minescene->m_rightMineNum++;
        }

        else if(2 == m_rMouseKeyNum)
        {
            m_isrightMouse = true;
            this->setPixmap(QPixmap(":/images/question1.png"));
            minescene->m_signalMineNum--;
            emit sig_resetMineNum(minescene->m_signalMineNum);
            if(this->m_isMine)
            {
                minescene->m_rightMineNum--;
            }
        }

        else if(3 == m_rMouseKeyNum)
        {
            m_isrightMouse = false;
            this->setPixmap(QPixmap(":/images/mine1.png"));
            m_rMouseKeyNum = 0;
        }
    }
}

void MineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // <1> check game state after releasing the mouse
    MineScene *minescene = (MineScene *)this->scene();
    if(minescene->m_isGameover || this->m_isOpened || this->m_isrightMouse)
    {
        return;
    }

    // <2> still in game, releasing makes sense
    if(event->button() == Qt::LeftButton)
    {
        if(1 == this->m_rMouseKeyNum)
            return;
        m_isOpened = true;
        if(m_isMine)
        {
            minescene->openAllItesm();
            minescene->m_isGameover = true;
            QMessageBox::information(
                        (QWidget*)minescene->parent(),
                        tr("game over"),
                        "You failed!\n Please try again.",
                        QMessageBox::Ok
                        );
            emit this->sig_restartGame();
            return;
        }
        else
        {
            if(!m_aroundMineNum)
            {
                this->setPixmap(QPixmap(":/images/mine0.png"));
                minescene->expenWater(this);

            }

            else
            {
                QString path = tr(":/images/") + QString::number(m_aroundMineNum) + tr(".png");
                this->setPixmap(QPixmap(path));
            }
        }

        minescene->m_remainNoMines--;
        if(!minescene->m_remainNoMines)
        {
            minescene->m_isGameover = true;
            minescene->openAllItesm();
            minescene->sig_successPassGame();
        }
    }
}
