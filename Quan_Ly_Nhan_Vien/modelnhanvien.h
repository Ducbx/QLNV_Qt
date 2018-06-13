#ifndef MODELNHANVIEN_H
#define MODELNHANVIEN_H
#include"nhanvien.h"
#include<QList>


class modelNhanVien
{
public:
    modelNhanVien();
public:
    QList<NhanVien*> arrNhanVien;
};

#endif // MODELNHANVIEN_H
