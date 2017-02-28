#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    QLabel *label;
    QTimer *timer;

    int i;
    int sum;
private slots:
    void get_sum();
};



#endif // MAINWINDOW_H
