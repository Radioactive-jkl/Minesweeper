/* * * * * * * * * * * * * * * *
 * definition of a single cell *
 * and its operation functions *
 * * * * * * * * * * * * * * * */

#ifndef MINEITEM_H
#define MINEITEM_H



#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMessageBox>


class MineItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MineItem(int t_x,int t_y,QPixmap pixmap,QGraphicsItem *parent = 0);
    int m_X;
    int m_Y;
    bool m_isMine;
    bool m_isOpened;
    int m_aroundMineNum;
    int m_rMouseKeyNum;
    bool m_isrightMouse;

    //opts of mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

    void sig_restartGame();
    void sig_resetMineNum(int t_signedMineNum);

public slots:
};



#endif // MINEITEM_H
