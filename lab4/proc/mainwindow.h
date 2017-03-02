#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QTableView>
#include <QStandardItemModel>
#include <QAbstractItemView>


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
    // main ui
    QTabWidget *tab;
    QWidget *basicInfo;
    QWidget *process;
    QWidget *used;



    // status line
    QLabel *label;
    QString status;
private slots:
    void updateStatus();
};

#endif // MAINWINDOW_H
