#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;


typedef struct _CPU CPU;
struct _CPU {
    char name[10];		// name
    // begin computer to now
    unsigned int user;	// user status time
    unsigned int nice;	// nice间
    unsigned int system;// system status time
    unsigned int idle;	// wait time expect IO
    unsigned int iowait;// wait IO
    unsigned int irq;	// handware interupt时间
    unsigned int softirq; // soft interupt时
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QLabel *label;
    QTimer *timer;
    FILE *fp;
    CPU cpu;
    CPU cpu1;
    CPU cpu2;
    CPU *cpu1p;
    CPU *cpu2p;

    void get_CPU(CPU &cpu);
private slots:
    void calu_CPU();
};

#endif // MAINWINDOW_H
