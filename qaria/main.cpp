#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    a.setWindowIcon(QIcon(":/images/icon.png"));
    w.setMinimumSize(QSize(950, 576));

    return a.exec();
}
