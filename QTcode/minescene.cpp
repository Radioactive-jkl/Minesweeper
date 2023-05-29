#include "minescene.h"
#include "common.h"

QString MineScene::minetype = "0";

QPoint t_around[8] =
{
    QPoint(-1,-1),
    QPoint(-1, 0),
    QPoint(-1, 1),
    QPoint( 0,-1),
    QPoint( 0, 1),
    QPoint( 1,-1),
    QPoint( 1, 0),
    QPoint( 1, 1)
};

MineScene::MineScene(QObject *parent) : QGraphicsScene(parent)
{
    m_signalMineNum = 0;
    m_rightMineNum = 0;
    this->m_isGameover = false;
    m_remainNoMines = 0;
}

//initialize scene of game
void MineScene::initscene()
{
    this->m_remainNoMines = m_scenecol * m_scenerow - m_minesum;
    for(int i = 0; i < m_scenerow; i++)
    {
        QVector<MineItem *> t_vec;
        for(int j = 0; j<m_scenecol;j++)
        {
            MineItem *t_item = new MineItem(i,j,QPixmap(":/images/mine1.png"));
            t_item->setPos(j * COMMON::MAPWIDTH,i* COMMON::MAPHEIGHT);
            this->addItem(t_item);
            t_vec.push_back(t_item);
        }
        this->m_itemVec.push_back(t_vec);
    }

    srand(time(NULL));
    for(int i = 0;i < m_minesum;i++)
    {
        int t_rows = rand()%m_scenerow;
        int t_cols = rand()%m_scenecol;

        if(!this->m_itemVec[t_rows][t_cols]->m_isMine)
        {
            this->m_itemVec[t_rows][t_cols]->m_isMine = true;
            this->countAroundMines(this->m_itemVec[t_rows][t_cols]);
        }
        else
            i--;
    }

    for(int i = 0;i< m_scenerow;i++)
    {
        for(int j = 0;j< m_scenecol;j++)
        {
            this->connect(this->m_itemVec[i][j],SIGNAL(sig_restartGame()),this,SIGNAL(sig_scenenewGame()));
            this->connect(this->m_itemVec[i][j],SIGNAL(sig_resetMineNum(int)),this,SIGNAL(sig_scenedisplayMineNum(int)));
        }
    }
}

void MineScene::countAroundMines(MineItem *item)
{
    if(NULL == item || !item->m_isMine)
        return;

    for(int i = 0;i < 8;i++)
    {
        int t_x = item->m_X + t_around[i].x();
        int t_y = item->m_Y + t_around[i].y();
        if(t_x < 0 || t_x >= this->m_scenerow || t_y < 0 || t_y >= this->m_scenecol)
            continue;
        if(m_itemVec[t_x][t_y]->m_isMine)
            continue;
        m_itemVec[t_x][t_y]->m_aroundMineNum++;
    }
}

void MineScene::openAllItesm()
{
    if(this->m_isGameover)
        return;

    for(int i = 0; i<m_scenerow; i++)
    {
        for(int j = 0; j < m_scenecol; j++)
        {
            m_itemVec[i][j]->m_isOpened = true;
            if(m_itemVec[i][j]->m_isMine)
            {
                QString pathbong = tr(":/images/") + tr("bong") + minetype + tr(".png");
                m_itemVec[i][j]->setPixmap(pathbong);
            }
            else
            {
                if(!m_itemVec[i][j]->m_aroundMineNum)
                     m_itemVec[i][j]->setPixmap(QPixmap(":/images/mine0.png"));
                else
                {
                    QString path = tr(":/images/") + QString::number(m_itemVec[i][j]->m_aroundMineNum) + tr(".png");
                    m_itemVec[i][j]->setPixmap(path);
                }
            }
        }
    }
}

void MineScene::expenWater(MineItem *item)
{
    if(NULL == item || item->m_isMine)
        return;

    for(int i = 0;i < 8;i++)
    {
        int t_x = item->m_X + t_around[i].x();
        int t_y = item->m_Y + t_around[i].y();

        if(t_x < 0 || t_x >= m_scenerow || t_y < 0 ||  t_y >= m_scenecol)
            continue;
        else if(m_itemVec[t_x][t_y]->m_isMine || m_itemVec[t_x][t_y]->m_isOpened)
            continue;
        else if(m_itemVec[t_x][t_y]->m_rMouseKeyNum > 0)
            continue;

        m_itemVec[t_x][t_y]->m_isOpened = true;
        this->m_remainNoMines--;
        int itemnum = m_itemVec[t_x][t_y]->m_aroundMineNum;

        if(0 == itemnum)
        {
            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine0.png"));

            expenWater(m_itemVec[t_x][t_y]);
        }

        else
        {
            QString path = tr(":/images/") + QString::number(m_itemVec[t_x][t_y]->m_aroundMineNum) + tr(".png");
            m_itemVec[t_x][t_y]->setPixmap(QPixmap(path));
        }
    }
    if(0 == m_remainNoMines)
    {
        m_isGameover = true;
        this->openAllItesm();
        emit sig_successPassGame();
    }
}
