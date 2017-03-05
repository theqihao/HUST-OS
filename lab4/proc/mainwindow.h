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
#include <QMessageBox>
#include <QProgressBar>
#include <QPainter>
#include <QWidget>
#include <QPen>
#include <QPixmap>
#include <QCursor>
#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include <QInputDialog>
#include <QByteArray>



// C/C++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <pwd.h> /* file own  */
#include <iostream>
#include <vector>
#include <algorithm>

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

    // process
    void showProcessInfo();
    int findProcess(vector<PRO> &ll, int x);
    void createRightMenu();
    // used
    void get_CPU(CPU &cpu);

private:
    Ui::MainWindow *ui;
    //

    // main ui, tab
    QTabWidget *tab;
    QWidget *basicInfo;
    QWidget *process;
    QWidget *used;
    // show process
    QTableView *tv;
    QStandardItemModel *model;

    int PID;
    QMenu *rightMenu;
    QAction *killAction;
    QAction *infoAction;



    // process info
    int ROWS;
    vector<PRO> list;
    vector<PRO> show_list;

    // used info
    // 1: cpu
    CPU cpu1;
    CPU cpu2;
    CPU *cpu1p;
    CPU *cpu2p;
    QLabel *cpu_label;
    QProgressBar *cpu_progressBar;
    vector<double> cpu_list;
    QLabel *cpu_graph;
    // 2:mem
    MEM mem;
    QLabel *mem_label;
    QProgressBar *mem_progressBar;
    vector<double> mem_list;
    QLabel *mem_graph;

    // status line
    QLabel *label;
    QString status_text;
private slots:
    void getProcessInfo();
    void clicked_rightMenu(const QPoint &pos);
    //
    void killProcess();
    void infoProcess();
private slots:
    void updateStatus();
    void calu_CPU();
    void cpu_line();
    // 内存使用率(MEMUsedPerc)=100*(MemTotal-MemFree-Buffers-Cached)/MemTotal
    void calu_MEM();
    void mem_line();

};


#endif // MAINWINDOW_H
