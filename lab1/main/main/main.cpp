#include "mainwindow.h"
#include "showsum.h"
#include "showcpu.h"
#include <stdio.h>
#include <unistd.h>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*
    ShowSum show_sum;
    show_sum.show();
    ShowCPU showCPU;
    showCPU.show();
    */

    int id1 = fork();
    if (id1 < 0) {
        cout << "fork() 1 error" << endl;
    } else if (id1 == 0) {
        cout << "child sum" << endl;
        execv("../build-showsum-Desktop-Debug/showsum", NULL);
    } else {
        int id2 = fork();
        if (id2 < 0) {
            cout << "fork() 2 error" << endl;
        } else if (id2 == 0) {
            cout << "child cpu" << endl;
            execv("../build-showCPU-Desktop-Debug/showCPU", NULL);
        }
    }


    return a.exec();
}


