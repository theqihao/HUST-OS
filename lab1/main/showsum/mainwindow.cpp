#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("show sum");
    this->resize(500, 100);  // size
    // init
    i = 0;
    sum = 0;
    // timer signal
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(get_sum()));
    timer->start(3000);

    // label show time
    label = new QLabel(this);
    QFont label_font("Courier", 20);
    label_font.setBold(true);
    label->setFont(label_font);
    QPalette pelette;
    pelette.setColor(QPalette::WindowText,Qt::blue);
    label->setPalette(pelette);
    label->setGeometry(QRect(30, 30, 400, 50)); //设local, size
    label->setText("Loading........");
}

void MainWindow::get_sum()
{
    if (i <= 100) {
        sum += i;
        i++;
    }

    // transter
    int temp = sum;
    char str[10];
    int xb = 0;
    while (temp >= 10) {
        str[xb] = temp % 10 + '1' - 1;
        temp /= 10;
        xb++;
    }
    str[xb] = temp % 10 + '1' - 1;
    xb++;
    str[xb] = '\0';
    char restr[10];
    for (int i = xb-1, j = 0; i >= 0; i--, j++) {
        restr[j] = str[i];
    }
    restr[xb] = '\0';

    cout << sum << endl;
    char final_str[30];
    sprintf(final_str, "Now sum is: %s\n", restr);
    label->setText(final_str);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
    delete timer;
}
