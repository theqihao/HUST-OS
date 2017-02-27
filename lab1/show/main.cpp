#include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton btn("hello world");
    btn.resize(200,100);
    btn.show();
    return app.exec();
}