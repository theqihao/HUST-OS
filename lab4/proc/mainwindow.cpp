#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000, 600);
    this->setWindowTitle("show proc");

    // status label
    label = new QLabel(this);
    label->setFixedSize(1000, 25);
    label->setText("              Loading......");
    QFont label_font("Courier", 16);
    label_font.setBold(true);
    label->setFont(label_font);
    statusBar()->addWidget(label);

    // init
    initTab();

    // timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStatus()));
   // connect(timer, SIGNAL(timeout()), this, SLOT(calu_CPU()));
   // connect(timer, SIGNAL(timeout()), this, SLOT(cpu_line()));
  //  connect(timer, SIGNAL(timeout()), this, SLOT(calu_MEM()));
   // connect(timer, SIGNAL(timeout()), this, SLOT(mem_line()));
    timer->start(1000);
}


void MainWindow::initTab() {
    // malloc space
    tab = new QTabWidget(this);
    tab->resize(1000, 572);
    basicInfo = new QWidget;
    process = new QWidget;
    used = new QWidget;
    // add
    tab->addTab(process, QString("process"));
    tab->addTab(used, QString("used"));

    tab->addTab(basicInfo, QString("basicInfo"));

    addBasicInfo();
    addProcess();
    addUsed();
}

void MainWindow::addBasicInfo() {
    QString final = "\n\n\n\n\n";
    char temp[200];
    char buf[100];
    FILE *fp;
    // name
    fp = fopen("/proc/sys/kernel/hostname", "r");
    if (fp == NULL) {
        cout << "open /proc/sys/kernel/hostnam error" << endl;
    }
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tHostname     :   %s\n", buf);
    final += QString(temp);
    // CPU info
    fp = popen("cat /proc/cpuinfo | grep name | awk -F: '{print $2}' | uniq -c", "r");
    if (fp == NULL) cout << "open cpuinfo error" << endl;
    memset(buf, 0, sizeof(buf));
    fread(buf, sizeof(buf), 1, fp);
    cout << buf << endl;
    int core;
    char info[50];
    sscanf(buf, "%d", &core);
    strncpy(info, buf + 9, 40);
    info[40] = '\0';
    sprintf(temp, "\tProcessor    :   %s  *  %d\n\n", info, core);
    final += QString(temp);
    // mem info
    fp = popen("cat /proc/meminfo | grep MemTotal | awk -F' ' '{print $2}' ", "r");
    if (fp == NULL) cout << "open meminfo error" << endl;
    int size;
    fscanf(fp, "%d", &size);
    sprintf(temp, "\tMemory       :   %.1lfGiB\n\n", 1.0 * size / 1024 / 1024);
    final += QString(temp);
    // version issue
    fp = fopen("/etc/issue", "r");
    if (fp == NULL) cout << "open issue error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tIssue ver    :   %.18s\n\n", buf);
    final += QString(temp);

    // version info
    fp = popen("cat /proc/version", "r");
    if (fp == NULL) cout << "open version error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tKernel ver   :   %.20s\n\n", buf);
    final += QString(temp);
    // OS type
    memset(buf, 0, sizeof(buf));
    fp = popen("uname -m", "r");
    if (fp == NULL) cout << "uname -m error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tOS type      :   %s\n", buf);
    final += QString(temp);
    cout << temp << endl;
    // open time
    // popen : syscall, exe shell, then return FILE*.
    // date -d : show time with string.
    // -F : define the separator.
    // date -d "$X second ago" : get the time befor X second, print format.
    memset(buf, 0, sizeof(buf));
    fp = popen("date -d \"$(awk -F. '{print $1}' /proc/uptime) second ago\" +\"%Y-%m-%d %H:%M:%S\"", "r");
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tPower time   :   %s\n", buf);
    final += QString(temp);

    // label
    QLabel *label_image = new QLabel(basicInfo);
    QPixmap pix = QPixmap(":/images/linux.png");
    label_image->setPixmap(pix);
    label_image->setGeometry(600, 0, 500, 180);
    QLabel *label = new QLabel(basicInfo);
    label->setText(final);
    QFont label_font("Courier", 16);
    label_font.setBold(true);
    label->setFont(label_font);
}

void MainWindow::addProcess() {
    tv = new QTableView(process);
    model = new QStandardItemModel();
    int i = 0;
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("Proecss name")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("User name")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("State")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("PID")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("PPID")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("%CPU")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("Memory (kB)")));
    model->setHorizontalHeaderItem(i++, new QStandardItem(QString("Priority")));

    tv->setModel(model);
    // size
    tv->resize(1000, 550);
    // column width
    i = 0;
    tv->setColumnWidth(i++,200);
    tv->setColumnWidth(i++,100);
    tv->setColumnWidth(i++,100);
    tv->setColumnWidth(i++,100);
    tv->setColumnWidth(i++,100);
    tv->setColumnWidth(i++,100);
    tv->setColumnWidth(i++,150);
    tv->setColumnWidth(i++,100);

    // set
    tv->setMouseTracking(true);
    // select row
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);


 //   getProcessInfo();
   // showProcessInfo();
}

void MainWindow::getProcessInfo() {
    PRO pro;
    DIR *dir = NULL;
    struct dirent *dirp = NULL;
    struct stat buf;
    char open_name[100];
    char full_name[100];
    char shell[100];
    char temp[100];


    // begin
    list.clear();
    dir = opendir("/proc");
    if (dir == NULL) {
        cout << "open /proc error" << endl;
    }
    while ((dirp = readdir(dir)) != NULL) {
        // if not process, continue
        char c = dirp->d_name[0];
        if (!(c >= '0' && c <= '9')) {
            continue;
        }
        // get full_name
        sprintf(full_name, "/proc/%s", dirp->d_name);
        lstat(full_name, &buf);
        // if is a dir,
        if (!S_ISDIR(buf.st_mode)) {
            continue;
        }
        // User
        if (getpwuid(buf.st_uid)->pw_name != NULL)
            strcpy(pro.user, getpwuid(buf.st_uid)->pw_name);
        // name
        sprintf(open_name, "%s/status", full_name);
        FILE *fp = fopen(open_name, "r");
        if (fp == NULL) {
            cout << "open " << open_name << " error" << endl;
            fclose(fp);
            continue;
        }
        fscanf(fp, "Name: %s\n", pro.name);

        // status
        fscanf(fp, "State: %s %s\n", pro.state, temp);

        // PID, PPID
/*
        sprintf(shell, "cat %s/status | grep Pid", full_name);
        fp = popen(shell, "r");
        if (fp == NULL) {
            cout << "open " << shell << "error" << endl;
            fclose(fp);
            continue;
        }
*/
        fscanf(fp, "Tgid:	%d\n", &pro.pid);
        fscanf(fp, "Ngid:	%d\n", &pro.ppid);

        fscanf(fp, "Pid:	%d\n", &pro.pid);
        fscanf(fp, "PPid:	%d\n", &pro.ppid);

        // mem  VmSize

        sprintf(shell, "cat %s/status | grep VmSize | awk -F' ' '{print $2}'", full_name);
        fp = popen(shell, "r");
        if (fp == NULL) {
            cout << "open " << shell << "error" << endl;
            fclose(fp);
            continue;
        }
        fscanf(fp, "%d", &pro.mem);

        // cpu



        // pri  nice

        sprintf(open_name, "%s/stat", full_name);
        fp = fopen(open_name, "r");
        fscanf(fp, "%d %s %s", &pro.pri, temp, temp);
        for (int i = 0; i < 16; i++) {
            fscanf(fp, "%d", &pro.pri);
        }
        // end
        fclose(fp);
        list.push_back(pro);
    }
    closedir(dir);

}

void MainWindow::showProcessInfo() {
    int row = model->rowCount();
    model->removeRows(0, row);// delete 0 ~ row
    //patient_model->removeRows(0, patient_model->rowCount());
    show_list.assign(list.begin(), list.end());
    for (unsigned int i = 0; i < show_list.size(); i++)
    {
        int j = 0;
        model->setItem(i, j++, new QStandardItem(QString(show_list[i].name)));
        model->setItem(i, j++, new QStandardItem(QString(show_list[i].user)));
        model->setItem(i, j++, new QStandardItem(QString(show_list[i].state)));
        model->setItem(i, j++, new QStandardItem(QString::number(show_list[i].pid)));
        model->setItem(i, j++, new QStandardItem(QString::number(show_list[i].ppid)));
        model->setItem(i, j++, new QStandardItem(QString::number(show_list[i].cpu)));
        model->setItem(i, j++, new QStandardItem(QString::number(show_list[i].mem)));
        model->setItem(i, j++, new QStandardItem(QString::number(show_list[i].pri)));
    }
}

void MainWindow::addUsed() {
    QFont label_font("Courier", 16);
    label_font.setBold(true);
    QPalette pelette;
    pelette.setColor(QPalette::WindowText,Qt::blue);

    // CPU label
    cpu_label = new QLabel(used);
    cpu_label->setFont(label_font);

    cpu_label->setPalette(pelette);
    cpu_label->setGeometry(QRect(20, 0, 300, 50)); //设local, size
    cpu_label->setText("Loading........");
    // CPU progressBar
    cpu_progressBar = new QProgressBar(used);
    cpu_progressBar->setRange(0,100);
    cpu_progressBar->setValue(0);
    cpu_progressBar->setOrientation(Qt::Horizontal);
    cpu_progressBar->setGeometry(QRect(300, 16, 600, 20));
    cpu_progressBar->setFont(label_font);
    cpu_progressBar->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; } QProgressBar::chunk { background-color: rgb(0, 0, 255) }");
    // cpu
    cpu_graph = new QLabel(used);
    cpu_graph->setGeometry(QRect(100, 50, 800, 160)); //设local, size

    // cpu x
    QLabel *cpu_x = new QLabel(used);
    cpu_x->setFont(label_font);
    cpu_x->setPalette(pelette);
    cpu_x->setGeometry(QRect(900, 10, 100, 200)); //设local, size
    cpu_x->setText("100%\n\n66%\n\n33%");
    // cpu y
    QLabel *cpu_y = new QLabel(used);
    cpu_y->setFont(label_font);
    cpu_y->setPalette(pelette);
    cpu_y->setGeometry(QRect(100, 200, 900, 50)); //设local, size
    cpu_y->setText("60                 40                    20                  0 (s)");

    // MEM label
    mem_label = new QLabel(used);
    mem_label->setFont(label_font);
    pelette.setColor(QPalette::WindowText,Qt::green);
    mem_label->setPalette(pelette);
    mem_label->setGeometry(QRect(20, 250, 300, 50)); //设local, size
    mem_label->setText("Loading........");

    // MEM progressBar
    mem_progressBar = new QProgressBar(used);
    mem_progressBar->setRange(0,100);
    mem_progressBar->setValue(0);
    mem_progressBar->setOrientation(Qt::Horizontal);
    mem_progressBar->setGeometry(QRect(300, 266, 600, 20));
    mem_progressBar->setFont(label_font);
    mem_progressBar->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; } QProgressBar::chunk { background-color: rgb(0, 255, 0) }");

    // mem
    mem_graph = new QLabel(used);
    mem_graph->setGeometry(QRect(100, 300, 800, 160)); //设local, size

    // mem x
    QLabel *mem_x = new QLabel(used);
    mem_x->setFont(label_font);
    mem_x->setPalette(pelette);
    mem_x->setGeometry(QRect(900, 260, 100, 200)); //设local, size
    mem_x->setText("100%\n\n66%\n\n33%");
    // mem y
    QLabel *mem_y = new QLabel(used);
    mem_y->setFont(label_font);
    mem_y->setPalette(pelette);
    mem_y->setGeometry(QRect(100, 450, 900, 50)); //设local, size
    mem_y->setText("60                 40                    20                  0 (s)");

    // init list
    for (int i = 0; i < 60; i++) {
        cpu_list.push_back(0);
        mem_list.push_back(0);
    }

    // calu CPU
    cpu1p = &cpu1;
    cpu2p = &cpu2;
    get_CPU(*cpu1p);
    cout << "addUsed finish" << endl;
}

void MainWindow::get_CPU(CPU &cpu)
{
    char buf[128];
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        QMessageBox::information(this, "error", "open file failed");
    }
    fgets(buf, sizeof(buf), fp);
    sscanf(buf, "%s %u %u %u %u %u %u %u", cpu.name, &cpu.user, &cpu.nice, &cpu.system, &cpu.idle, &cpu.iowait, &cpu.irq, &cpu.softirq);
    fclose(fp);
}

void MainWindow::calu_CPU()
{
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
    double cpu_res = (1 - (sub_idle) / (sub_sum)) * 100;

    cpu_progressBar->setValue((int) cpu_res);
    cpu_label->setText("CPU used : " + QString::number(cpu_res, 10, 2) + "%");
    cpu_list.push_back(cpu_res);
    while (cpu_list.size() > 60) {
        cpu_list.erase(cpu_list.begin());
    }
    CPU *temp = cpu1p;
    cpu1p = cpu2p;
    cpu2p = temp;
}

void MainWindow::cpu_line() {
    /*
    cpu_list.clear();
    for (int i = 0; i < 10; i++) {
        cpu_list.push_back(27);
    }
    for (int i = 0; i < 10; i++) {
        cpu_list.push_back(25);
    }
    for (int i = 0; i < 20; i++) {
        cpu_list.push_back(75);
    }
    for (int i = 0; i < 20; i++) {
        cpu_list.push_back(33);
    }
*/
    QPixmap cpu_pix(800, 200);
    QPainter cpu_painter(&cpu_pix);
    QPen cpu_pen(Qt::blue);
    //cpu_pen.setCapStyle(Qt::RoundCap);
    cpu_pen.setJoinStyle(Qt::RoundJoin);
    cpu_painter.setPen(cpu_pen);
    cpu_painter.setBrush(QBrush(Qt::white));
    cpu_painter.drawRect(0, 18, 800, 160);
    cpu_pen.setWidth(2);
    cpu_painter.setPen(cpu_pen);
    for (int i = 0; i < 3; i++) {
        cpu_painter.drawLine(0, 19 + 160 * (1 - i * 33 / 100.0), 1000, 19 + 160 * (1 - (i) * 33 / 100.0));
    }
    //cpu_painter.drawLine(0, 30, 300, 400);
    // drawLine(int x1, int y1, int x2, int y2)
    cpu_pen.setColor(Qt::black);
    cpu_painter.setPen(cpu_pen);
    for (unsigned int i = 1; i < cpu_list.size(); i++) {
        cpu_painter.drawLine((i-1) * 820 / 60.0, 19 + 160 * (1 - cpu_list[i-1]/100), i * 820 / 60.0, 19 + 160 * (1 - cpu_list[i]/100));
    }
    cpu_graph->setPixmap(cpu_pix);
}

void MainWindow::calu_MEM() {
    FILE *fp = popen("cat /proc/meminfo | grep MemTotal | awk -F' ' '{print $2}'", "r");
    if (fp == NULL) {
        QMessageBox::information(this, "error", "open file failed");
    }
    fscanf(fp, "%ud", &mem.total);
    fp = popen("cat /proc/meminfo | grep MemFree | awk -F' ' '{print $2}'", "r");
    if (fp == NULL) {
        QMessageBox::information(this, "error", "open file failed");
    }
    fscanf(fp, "%ud", &mem.free);
    fp = popen("cat /proc/meminfo | grep Buffers | awk -F' ' '{print $2}'", "r");
    if (fp == NULL) {
        QMessageBox::information(this, "error", "open file failed");
    }
    fscanf(fp, "%ud", &mem.buffer);
    fp = popen("cat /proc/meminfo | grep Cached | awk -F' ' '{print $2}'", "r");
    if (fp == NULL) {
        QMessageBox::information(this, "error", "open file failed");
    }
    fscanf(fp, "%ud", &mem.cached);
    fclose(fp);
    MEM mem_show = mem;
    //cout << mem.total << " " << mem.free << " " << mem.buffer << " " <<  mem.cached << endl;
    // 内存使用率(MEMUsedPerc)=100*(MemTotal-MemFree-Buffers-Cached)/MemTotal
    double mem_res = 100.0 * (mem_show.total - mem_show.free - mem_show.buffer - mem_show.cached) / (1.0 * mem_show.total);
    mem_progressBar->setValue((int) mem_res);
    mem_label->setText("MEM used : " + QString::number(mem_res, 10, 2) + "%");
    mem_list.push_back(mem_res);
    while (mem_list.size() > 60) {
        mem_list.erase(mem_list.begin());
    }
}

void MainWindow::mem_line() {
    QPixmap mem_pix(800, 200);
    QPainter mem_painter(&mem_pix);
    QPen mem_pen(Qt::green);

    //cpu_pen.setCapStyle(Qt::RoundCap);
    mem_pen.setJoinStyle(Qt::RoundJoin);
    mem_painter.setPen(mem_pen);
    mem_painter.setBrush(QBrush(Qt::white));
    mem_painter.drawRect(0, 18, 800, 160);
    mem_pen.setWidth(2);

    mem_painter.setPen(mem_pen);
    for (int i = 0; i < 3; i++) {
        mem_painter.drawLine(0, 19 + 160 * (1 - i * 33 / 100.0), 1000, 19 + 160 * (1 - (i) * 33 / 100.0));
    }

    //cpu_painter.drawLine(0, 30, 300, 400);
    // drawLine(int x1, int y1, int x2, int y2)
    mem_pen.setColor(Qt::black);
    mem_painter.setPen(mem_pen);
    for (unsigned int i = 1; i < mem_list.size(); i++) {
        if (mem_list[i-1] == 0) continue;
        mem_painter.drawLine((i-1) * 820 / 60.0, 19 + 160 * (1 - mem_list[i-1]/100), i * 820 / 60.0, 19 + 160 * (1 - mem_list[i]/100));
    }
    mem_graph->setPixmap(mem_pix);
}


void MainWindow::updateStatus() {
    QDateTime time = QDateTime::currentDateTime();
    status_text = "\tnow time :";
    status_text += time.toString("  yyyy-MM-dd hh:mm:ss");
    // run time
    char temp[100];
    FILE *fp = fopen("/proc/uptime", "r");
    double run_time;
    fscanf(fp, "%lf ", &run_time);
    int hour = run_time / 3600;
    int minite = (run_time - hour * 3600) / 60;
    int second = (run_time - hour * 3600 - minite * 60);
    sprintf(temp, "\t\trun time : %dh : %dm : %ds", hour, minite, second);
    status_text += QString(temp);
    label->setText(status_text);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete basicInfo;
    delete process;
    delete used;
    delete tab;

    // cpu
    delete cpu_label;
    delete cpu_progressBar;
    delete cpu_graph;
    // mem
    delete mem_label;
    delete mem_progressBar;
    delete mem_graph;
    // status line
    delete label;
}
