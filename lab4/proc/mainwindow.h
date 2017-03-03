#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// file
#include "head.h"

// Qt
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
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QColor>
#include <QBrush>

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
    // info
    void getProcessInfo();
    void showProcessInfo();
private:
    Ui::MainWindow *ui;
    // main ui, tab
    QTabWidget *tab;
    QWidget *basicInfo;
    QWidget *process;
    QWidget *used;
    // show process
    QTableView *tv;
    // process info
    vector<PRO> pro_list;



    // status line
    QLabel *label;
    QString status;
private slots:
    void updateStatus();
};

#endif // MAINWINDOW_H
