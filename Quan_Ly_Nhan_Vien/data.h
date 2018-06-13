#ifndef DATA_H
#define DATA_H
#include<QList>
#include"nhanvien.h"



class Data
{
public:
    QList<NhanVien*> arrNhanVien;
public:
    Data();
    int kiemtraNV(QList<NhanVien*> arr, QString manv);
};

#endif // DATA_H
