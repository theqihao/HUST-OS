#ifndef SHOWSUM_H
#define SHOWSUM_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;


namespace Ui {
class ShowSum;
}

class ShowSum : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShowSum(QWidget *parent = 0);
    ~ShowSum();
    
private:
    Ui::ShowSum *ui;
    QLabel *label;
    QTimer *timer;

    int i;
    int sum;
private slots:
    void get_sum();
};

#endif // SHOWSUM_H
