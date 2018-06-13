#include "searchwindow.h"
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QGridLayout>
#include"quanlynhanvienui.h"
#include"nhanvien.h"
#include<QWidget>
#include"control.h"
#include<QMessageBox>

Searchwindow::Searchwindow(QWidget *parent)
    :QDialog(parent)
{
    QPushButton *btnSearch = new QPushButton("Search",this);
    QLabel *lbType = new QLabel("Nhap tieu chi tim kiem ", this);
    QLabel *lbcontent = new QLabel(" Nhap noi dung tim kiem", this);
    lineeditSearch = new QLineEdit(this);
    comboType = new QComboBox();
    QStringList strlistSearch;//= {"Tim kiem theo Ma NV","Tim kiem theo ten NV"};
    strlistSearch.append("Tim kiem theo Ma NV");
    strlistSearch.append("Tim kiem theo ten NV");
    comboType->addItems(strlistSearch);

    QGridLayout *gridSearch = new QGridLayout(this);
    gridSearch->addWidget(lbType,0,0);
    gridSearch->addWidget(comboType,0,1);
    gridSearch->addWidget(lbcontent,1,0);
    gridSearch->addWidget(lineeditSearch,1,1);
    gridSearch->addWidget(btnSearch,2,0,1,2);

    setLayout(gridSearch);

    connect(btnSearch,SIGNAL(clicked(bool)),this, SLOT(btnSearchClick()));
}

void Searchwindow::btnSearchClick()
{
    int row = Control::getInstace()->kiemtra(lineeditSearch->text());
    if(row== -1)QMessageBox::warning(this, "Cảnh báo", "Khong co nhan vien can tim!");
    else{
        emit showResult(row);
    }
}

