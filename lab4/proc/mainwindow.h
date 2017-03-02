#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>


// C/C++
#include <stdio.h>
#include <string.h>
#include <iostream>

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

    // Tab
    void initTab();
    void addBasicInfo();
    void addProcess();
    void addUsed();

private:
    Ui::MainWindow *ui;
    QTabWidget *tab;
    QWidget *basicInfo;
    QWidget *process;
    QWidget *used;

};

#endif // MAINWINDOW_H
