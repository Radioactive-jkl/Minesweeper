/* * * * * * * * * * * * * * * *
 * definition of a game scene  *
 * and some tool functions     *
 * * * * * * * * * * * * * * * */

#ifndef MINESCENE_H
#define MINESCENE_H



#include <QObject>
#include <QGraphicsScene>
#include <QVector>
#include <time.h>

#include "mineitem.h"


class MineScene :public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MineScene(QObject *parent = 0);
    QVector <QVector<MineItem *>> m_itemVec;
    int m_scenerow;
    int m_scenecol;
    int m_minesum;
    int m_crrentleve;
    int m_signalMineNum;
    int m_rightMineNum;
    bool m_isGameover;
    int m_remainNoMines;
    static QString minetype;

    void initscene();
    void countAroundMines(MineItem *t_item);
    void openAllItesm();
    void expenWater(MineItem *t_item);

signals:
    void sig_successPassGame();
    void sig_scenenewGame();
    void sig_scenedisplayMineNum(int);

public slots:
};



#endif // MINESCENE_H
