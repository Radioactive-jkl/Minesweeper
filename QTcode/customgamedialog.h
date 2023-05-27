/* * * * * * * * * * * * * * * *
 * A pop-up window for custom  *
 * gamemode settings           *
 * * * * * * * * * * * * * * * */

#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H



#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>


class CustomGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomGameDialog(QWidget *parent = 0);

    QSpinBox *colspinbox;
    QSpinBox *rowspinbox;
    QSpinBox *minenumspinbox;

    //function: read regedit settings
    void readsettings();

    //function: write regedit settings
    void writesetting();

signals:
    //function: signals for custom game
    void signal_sendCustomset(int,int,int);

public slots:
    //function: accept slots
    void slot_accepttok();
};



#endif // CUSTOMGAMEDIALOG_H
