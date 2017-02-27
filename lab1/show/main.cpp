#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton btn("hello world");
    btn.resize(200,100);
    btn.show();

	QTimer *timer = new QTimer(this);  
   	connect(timer,SIGNAL(timeout()),this,SLOT(timeoutslot()));//timeoutslot()为自定义槽  
   	timer->start(1000);  
    return app.exec();
}