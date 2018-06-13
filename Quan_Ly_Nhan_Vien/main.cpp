#include"quanlynhanvienui.h"
#include<QApplication>
#include<QWidget>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QuanLyNhanVienUI window;
    window.setFixedWidth(650);
    window.show();

    return app.exec();
}
