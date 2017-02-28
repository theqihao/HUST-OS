#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(500, 100);  // size
    this->setWindowTitle("show time");

    // timer signal
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setText()));
    timer->start(1000);

    // label show time
    label = new QLabel(this);
    QFont label_font("Courier", 20);
    label_font.setBold(true);
    label->setFont(label_font);
    QPalette pelette;
    pelette.setColor(QPalette::WindowText,Qt::green);
    label->setPalette(pelette);

    label->setGeometry(QRect(30, 30, 400, 50)); //设local, size
}

void MainWindow::setText()
{
    struct tm *local;
    time_t t;
    // time_t time(time_t * timer);
    // NULL ---> now time
    t = time(NULL);
    // localtime()间---> trans to local time
    local = localtime(&t);
    char s[100];
    sprintf(s, "Local time is : %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
    label->setText(s);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
    delete timer;
}
