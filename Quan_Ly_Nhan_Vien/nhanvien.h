#ifndef NHANVIEN_H
#define NHANVIEN_H
#include<QObject>
#include<QDate>


class NhanVien
{
private:
    QString MaNhanVien;
    QString HoTen;
    float HeSoLuong;
    QString GioiTinh;
    QString NgaySinh;
    QString PhongBan;
public:
    NhanVien();
    NhanVien(QString manv, QString hoten, float heso, QString gioitinh, QString ngaysinh, QString phongban );
    ~NhanVien();

    void setManv(QString manv);
    QString getManv();
    void setTennv(QString tennv);
    QString getTennv();
    void setHeso(float heso);
    float getHeso();
    void setGioitinh(QString gioitinh);
    QString getGioitinh();
    void setNgaysinh(QString ngaysinh);
    QString getNgaySinh();
    void setPhongban(QString phongban);
    QString  getPhongban();
};

#endif // NHANVIEN_H
