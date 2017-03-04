#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class MyPainter;
}

class MyPainter : public QWidget
{
    Q_OBJECT

public:
    explicit MyPainter(QWidget *parent = 0);
    ~MyPainter();

    //
    void paintEvent(QPaintEvent *event);
private:
    Ui::MyPainter *ui;

};

#endif // MYPAINTER_H
