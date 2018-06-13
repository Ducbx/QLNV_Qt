#include "nhanvien.h"
#include<QObject>

NhanVien::NhanVien()
{
    HoTen = "";
    MaNhanVien = "";
    HeSoLuong = 0;
    NgaySinh = "";
    GioiTinh = "";
    PhongBan = "";
}

NhanVien::NhanVien(QString manv, QString hoten, float heso, QString gioitinh, QString ngaysinh, QString phongban)
{
    MaNhanVien = manv;
    HoTen = hoten;
    HeSoLuong = heso;
    GioiTinh = gioitinh;
    NgaySinh = ngaysinh;
    PhongBan = phongban;
}

void NhanVien::setManv(QString manv)
{
    MaNhanVien = manv;
}
QString NhanVien::getManv()
{
    return MaNhanVien;
}
void NhanVien::setTennv(QString tennv)
{
    HoTen = tennv;
}
QString NhanVien::getTennv(){
    return HoTen;
}
void NhanVien::setGioitinh(QString gioitinh)
{
    GioiTinh = gioitinh;
}
QString NhanVien::getGioitinh()
{
    return GioiTinh;
}
void NhanVien::setHeso(float heso)
{
    HeSoLuong = heso;
}
float NhanVien::getHeso()
{
    return HeSoLuong;
}
void NhanVien::setNgaysinh(QString ngaysinh)
{
    NgaySinh = ngaysinh;
}
QString NhanVien::getNgaySinh()
{
    return NgaySinh;
}
void NhanVien::setPhongban(QString phongban)
{
    PhongBan = phongban;
}
QString NhanVien::getPhongban()
{
    return PhongBan;
}
