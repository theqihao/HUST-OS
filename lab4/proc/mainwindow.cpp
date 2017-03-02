#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000, 600);
    this->setWindowTitle("show proc");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    timer->start(1000);

    label = new QLabel(this);
    label->setText("              Loading......");
    QFont label_font("Courier", 16);
    label_font.setBold(true);
    label->setFont(label_font);
    label->setGeometry(0, 550, 1000, 50);
    // init
    initTab();
}


void MainWindow::initTab() {
    // malloc space
    tab = new QTabWidget(this);
    tab->resize(1000, 550);
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
    strncpy(info, buf + 9, 30);
    sprintf(temp, "\tProcessor    :   %s  *  %d\n\n", info, core);
    final += QString(temp);
    // mem info
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) cout << "open meminfo error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    int size;
    sscanf(buf, "MemTotal:        %d kB", &size);
    sprintf(temp, "\tMemory       :   %.1lfGiB\n\n", 1.0 * size / 1024 / 1024);
    final += QString(temp);

    // version issue
    fp = fopen("/etc/issue", "r");
    if (fp == NULL) cout << "open issue error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tIssue num    :   %.18s\n\n", buf);
    final += QString(temp);

    // version info
    fp = popen("cat /proc/version", "r");
    if (fp == NULL) cout << "open version error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tKernel num   :   %.20s\n\n", buf);
    final += QString(temp);

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
    // run time
    fp = fopen("/proc/uptime", "r");
    fread(buf, sizeof(buf), 1, fp);
    double run_time;
    sscanf(buf, "%lf ", &run_time);
    cout << buf << endl;
    cout << run_time << endl;
    int hour = run_time / 3600;
    int minite = (run_time - hour * 3600) / 60;
    int second = (run_time - hour * 3600 - minite * 60);
    sprintf(temp, "\tRun time     :   %d hour %d minite %d second\n\n", hour, minite, second);
    final += QString(temp);
    // OS type
    memset(buf, 0, sizeof(buf));
    fp = popen("uname -m", "r");
    if (fp == NULL) cout << "uname -m error" << endl;
    fread(buf, sizeof(buf), 1, fp);
    sprintf(temp, "\tOS type      :   %s\n", buf);
    final += QString(temp);
    cout << temp << endl;
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
    QTableView *tv = new QTableView(process);
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("病人姓名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("病人性别")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("病人年龄")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("病人序号")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("病人优先等级 ")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("病人到达时间 ")));
    tv->setModel(model);

    tv->resize(1000, 550);


    tv->setMouseTracking(true);
    // select row
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::addUsed() {

}


void MainWindow::updateStatus() {
    QDateTime time = QDateTime::currentDateTime();
    status = time.toString("  yyyy-MM-dd hh:mm:ss");
    // status line
    label->setText(status);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tab;
    delete basicInfo;
    delete process;
    delete used;
}
