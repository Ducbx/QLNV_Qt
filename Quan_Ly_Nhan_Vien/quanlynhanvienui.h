#ifndef QUANLYNHANVIENUI_H
#define QUANLYNHANVIENUI_H
#include"nhanvien.h"
#include<QWidget>
#include<QStandardItemModel>
#include<QLineEdit>
#include<QDateEdit>
#include<QComboBox>
#include<QRadioButton>
#include<QList>
#include<QTableView>
#include"searchwindow.h"

class QuanLyNhanVienUI: public QWidget
{
    Q_OBJECT
public:
    QuanLyNhanVienUI(QWidget *parent=0);
private slots:
    void addBtnClick();
    void searchbtnClick();
    void deleteBtnClick();
    void sortBtnClick();
    void changeBtnClick();
    void tableClick();
    void onShowResult(int);
private:
    QLineEdit *m_lineeditManv ;
    QLineEdit *m_lineeditTennv;
    QLineEdit *m_lineeditLuongnv;
    QDateEdit *m_dateNV;
    QComboBox *m_comboPhong;
    QRadioButton *m_rdbtnNam;
    QRadioButton *m_rdbtnNu;
    QTableView *m_listNV;
    int soluong=0;
    QStandardItemModel *m_model;

    Searchwindow *m_newwin;
private:
    void ssshowTable(QList<NhanVien*> arr,int k);
};

#endif // QUANLYNHANVIENUI_H
