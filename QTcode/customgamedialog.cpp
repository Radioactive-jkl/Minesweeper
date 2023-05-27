#include "customgamedialog.h"


CustomGameDialog::CustomGameDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle("Custom Game");
    QLabel *label_1 = new QLabel("columns");
    QLabel *label_2 = new QLabel("rows");
    QLabel *label_3 = new QLabel("mines");

    colspinbox = new QSpinBox;
    colspinbox->setRange(10,100);
    colspinbox->setSingleStep(1);
    colspinbox->setValue(10);

    rowspinbox = new QSpinBox;
    rowspinbox->setRange(10,100);
    rowspinbox->setSingleStep(1);
    rowspinbox->setValue(10);

    minenumspinbox = new QSpinBox;
    minenumspinbox->setRange(1,100);
    minenumspinbox->setSingleStep(10);
    minenumspinbox->setValue(10);

    QPushButton *confirm_button = new QPushButton("confirm");
    QPushButton *cancel_button = new QPushButton("cancel");
    QGridLayout *glayout = new QGridLayout(this);

    glayout->addWidget(label_1,0,0);
    glayout->addWidget(rowspinbox,0,1);
    glayout->addWidget(label_2,1,0);
    glayout->addWidget(colspinbox,1,1);

    glayout->addWidget(label_3,2,0);
    glayout->addWidget(minenumspinbox,2,1);
    glayout->addWidget(confirm_button,3,0);
    glayout->addWidget(cancel_button,3,1);

    this->readsettings();
    this->connect(confirm_button,SIGNAL(clicked(bool)),this,SLOT(slot_accepttok()));
    this->connect(cancel_button,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void CustomGameDialog::readsettings()
{
    QSettings *setting = new QSettings("Get_arg","mine",this);
    setting->beginGroup("customGame");
    int row = setting->value("custom_row",10).toInt();
    int col = setting->value("custom_col",10).toInt();
    int mine = setting->value("custom_mine",11).toInt();

    setting->endGroup();
    rowspinbox->setValue(row);
    colspinbox->setValue(col);
    minenumspinbox->setValue(mine);
}

void CustomGameDialog::writesetting()
{
    QSettings *setting = new QSettings("Get_arg","mine",this);
    setting->beginGroup("customGame");

    setting->setValue("custom_row",rowspinbox->value());
    setting->setValue("custom_col",colspinbox->value());
    setting->setValue("custom_mine",minenumspinbox->value());
    setting->endGroup();
}

void CustomGameDialog::slot_accepttok()
{
    int row = rowspinbox->value();
    int col = colspinbox->value();
    int count = minenumspinbox->value();
    emit this->signal_sendCustomset(row,col,count);
    this->writesetting();
    this->close();
}
