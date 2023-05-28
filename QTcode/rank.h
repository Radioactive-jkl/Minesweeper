/* * * * * * * * * * * * * * * *
 * A new mode for competition  *
 *                             *
 * You can save your record    *
 * * * * * * * * * * * * * * * */

#ifndef RANK_H
#define RANK_H



#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QSettings>
#include <QString>


class rank : public QDialog
{
    Q_OBJECT
public:
    explicit rank(QWidget *parent = 0);

    QLabel *primarrecordtimelabel;
    QLabel *primarrecordnamelabel;
    QLabel *middlerecordtimelabel;
    QLabel *middlerecordnamelabel;
    QLabel *seniorrecordtimelabel;
    QLabel *seniorrecordnamelabel;

    void readsettings();
    void inti_rankrecord();

public slots:
    void slot_reset();

};



#endif // RANK_H
