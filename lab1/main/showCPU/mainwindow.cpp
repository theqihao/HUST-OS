#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("show CPU");
    this->resize(500, 100);  // size

    // timer signal
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(calu_CPU()));
    timer->start(2000);

    // label show time
    label = new QLabel(this);
    QFont label_font("Courier", 20);
    label_font.setBold(true);
    label->setFont(label_font);
    QPalette pelette;
    pelette.setColor(QPalette::WindowText,Qt::green);
    label->setPalette(pelette);
    label->setGeometry(QRect(30, 30, 400, 50)); //设local, size
    label->setText("Loading........");
    cpu1p = &cpu1;
    cpu2p = &cpu2;
    get_CPU(*cpu1p);
}

void MainWindow::get_CPU(CPU &cpu)
{
    char buf[128];
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        QMessageBox::information(this, "error", "open file failed");
    }
    fgets(buf, sizeof(buf), fp);
    sscanf(buf, "%s %u %u %u %u %u %u %u", cpu.name, &cpu.user, &cpu.nice, &cpu.system, &cpu.idle, &cpu.iowait, &cpu.irq, &cpu.softirq);
    fclose(fp);
}


void MainWindow::calu_CPU()
{
    //get_CPU(cpu);

  /*  printf("%s %u %u %u %u %u %u %u", cpu.name, cpu.user, cpu.nice, \
           cpu.system, cpu.idle, cpu.iowait, cpu.irq, cpu.softirq);
*/
    get_CPU(*cpu2p);


    /*
    CPU t1 to t2 sum = (user2+ nice2+ system2+ idle2+ iowait2+ irq2+ softirq2) - ( user1+ nice1+ system1+ idle1+ iowait1+ irq1+ softirq1)
    CPU t1 to t2时idle = (idle2 - idle1)
    CPU used =  1 - idle / sum间
    */
    double sum1 = cpu1p->user + cpu1p->nice + cpu1p->system + cpu1p->idle + cpu1p->iowait + cpu1p->irq + cpu1p->softirq;
    double sum2 = cpu2p->user + cpu2p->nice + cpu2p->system + cpu2p->idle + cpu2p->iowait + cpu2p->irq + cpu2p->softirq;
    double sub_sum = sum2 - sum1;
    double sub_idle = cpu2p->idle - cpu1p->idle;
    double ans = (1 - (sub_idle) / (sub_sum)) * 100;
    char str[50];
    /*
    sprintf(str, "%s %u %u %u %u %u %u %u", cpu.name, cpu.user, cpu.nice, \
               cpu.system, cpu.idle, cpu.iowait, cpu.irq, cpu.softirq);
    */
    //sprintf(str, "%s", );
    label->setText("Now CPU is: " + QString::number(ans, 10, 4) + "%");

    CPU *temp = cpu1p;
    cpu1p = cpu2p;
    cpu2p = temp;
}



MainWindow::~MainWindow()
{
    delete ui;
    delete label;
    delete timer;
}
