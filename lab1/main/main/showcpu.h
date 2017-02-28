#ifndef SHOWCPU_H
#define SHOWCPU_H

#include <QDialog>
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
class ShowCPU;
}

class ShowCPU : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShowCPU(QWidget *parent = 0);
    ~ShowCPU();
    
private:
    Ui::ShowCPU *ui;
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

#endif // SHOWCPU_H
