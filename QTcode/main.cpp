/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * Platform: Qt creator 5.14.2                     *
 * Author: Radioactive-jkl                         *
 * https://github.com/Radioactive-jkl/Minesweeper  *
 * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <QApplication>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    //To be compatible with my 4K screen
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    Mainwindow w;
    w.show();

    return a.exec();
}
