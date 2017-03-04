#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000, 600);
    this->setWindowTitle("show proc");

    // timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStatus()));

 //   connect(timer, SIGNAL(timeout()), this, SLOT(getProcessInfo()));

    timer->start(1000);


    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(getProcessInfo()));
    //timer->start(3000);

    // label
    label = new QLabel(this);
    label->setFixedSize(1000, 25);
    label->setText("              Loading......");
    QFont label_font("Courier", 16);
    label_font.setBold(true);
    label->setFont(label_font);
    statusBar()->addWidget(label);
    // init
    initTab();
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


    getProcessInfo();
    showProcessInfo();
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
            continue;
        }
        fscanf(fp, "Name: %s\n", pro.name);

        // status
        fscanf(fp, "State: %s (%s)\n", pro.state, temp);

        // PID, PPID

        sprintf(shell, "cat %s/status | grep Pid", full_name);
        fp = popen(shell, "r");
        if (fp == NULL) {
            cout << "open " << shell << "error" << endl;
            continue;
        }

       // fscanf(fp, "Tgid:	%d\n", &pro.pid);
        //fscanf(fp, "Ngid:	%d\n", &pro.ppid);

        fscanf(fp, "Pid:	%d\n", &pro.pid);
        fscanf(fp, "PPid:	%d\n", &pro.ppid);

        // mem  VmSize
        sprintf(shell, "cat %s/status | grep VmSize | awk -F' ' '{print $2}'", full_name);
        fp = popen(shell, "r");
        if (fp == NULL) {
            cout << "open " << shell << "error" << endl;
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
    tab->addTab(basicInfo, QString("basicInfo"));

    tab->addTab(used, QString("used"));
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


void MainWindow::updateStatus() {
    QDateTime time = QDateTime::currentDateTime();
    status = "\tnow time :";
    status += time.toString("  yyyy-MM-dd hh:mm:ss");
    // run time
    char temp[100];
    FILE *fp = fopen("/proc/uptime", "r");
    double run_time;
    fscanf(fp, "%lf ", &run_time);
    int hour = run_time / 3600;
    int minite = (run_time - hour * 3600) / 60;
    int second = (run_time - hour * 3600 - minite * 60);
    sprintf(temp, "\t\trun time : %d : %d : %d", hour, minite, second);
    status += QString(temp);
    label->setText(status);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete basicInfo;
    delete process;
    delete used;
    delete tab;
}
