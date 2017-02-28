#include "showsum.h"
#include "ui_showsum.h"

ShowSum::ShowSum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowSum)
{
    ui->setupUi(this);
    this->setWindowTitle("show sum");
    this->resize(500, 100);  // size

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
    pelette.setColor(QPalette::WindowText,Qt::green);
    label->setPalette(pelette);

    label->setGeometry(QRect(30, 30, 400, 50)); //设local, size

    i = 0;
    sum = 0;
}

void ShowSum::get_sum()
{
    if (i <= 100) {
        sum += i;
        i++;
    }
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
    label->setText(restr);
}

ShowSum::~ShowSum()
{
    delete ui;
    delete label;
    delete timer;
}
