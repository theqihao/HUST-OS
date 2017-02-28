#include "mainwindow.h"
#include "showsum.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ShowSum s;
    s.show();
    return a.exec();
}
