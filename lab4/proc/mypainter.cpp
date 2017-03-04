#include "mypainter.h"
#include "ui_mypainter.h"

MyPainter::MyPainter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyPainter)
{
    ui->setupUi(this);
}

void MyPainter::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter pa;
    pa.begin(this);
    pa.drawLine(500, 200, 800, 300);
    pa.end();
}

MyPainter::~MyPainter()
{
    delete ui;
}
