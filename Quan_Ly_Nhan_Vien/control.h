#ifndef CONTROL_H
#define CONTROL_H
#include<QList>
#include"nhanvien.h"
#include<QStandardItem>

class Control
{
private:
    Control();


public:
    QList<NhanVien*> arrNhanVien;
public:
    static Control* getInstace();

    int kiemtra(QString manv);
};

#endif // CONTROL_H
