#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <utility>
#include <QPair>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    //w.setVector();
    w.show();

    return a.exec();
}
