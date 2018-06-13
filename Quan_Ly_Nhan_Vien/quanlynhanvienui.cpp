#include "quanlynhanvienui.h"
#include "nhanvien.h"
#include"searchwindow.h"
#include"control.h"
#include"modelnhanvien.h"
#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QDateEdit>
#include<QRadioButton>
#include<QLabel>
#include<QComboBox>
#include<QGroupBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QStringList>
#include<QListView>
#include<QSplitter>
#include<QStandardItemModel>
#include<QTableView>
#include<QMessageBox>
#include<QList>
#include <QDebug>

QuanLyNhanVienUI::QuanLyNhanVienUI(QWidget *parent)
    :QWidget(parent)
{
    QPushButton *btnAdd= new QPushButton("Add", this);
    QPushButton *btnDel= new QPushButton("Delete",this);
    QPushButton *btnChange= new QPushButton("Change",this);
    QPushButton *btnSearch = new QPushButton("Search",this);
    QPushButton *btnSort = new QPushButton("Sort",this);
    QPushButton *btnExit= new QPushButton("Exit",this);
    QHBoxLayout *LayBtn= new QHBoxLayout();
    LayBtn->addWidget(btnAdd);
    LayBtn->addWidget(btnDel);
    LayBtn->addWidget(btnChange);
    LayBtn->addWidget(btnSearch);
    LayBtn->addWidget(btnSort);
    LayBtn->addWidget(btnExit);
    QGroupBox *groupBtn = new QGroupBox();
    groupBtn->setLayout(LayBtn);                                              //khi gọi VHbox/VBox chi can hbox->addWidget(grpBox)

    QLabel *lbManv = new QLabel("Mã nhân viên",this);
    QLabel *lbTennv = new QLabel("Tên nhân viên",this);
    QLabel *lbNgaysinh = new QLabel("Ngày sinh",this);
    QLabel *lbHeso = new QLabel("Hệ số lương",this);
    QLabel *lbGioitinh = new QLabel("Giới tính",this);
    QLabel *lbPhongban = new QLabel("Phòng ban", this);

    m_lineeditManv = new QLineEdit(this);
    m_lineeditTennv= new QLineEdit(this);
    m_lineeditLuongnv = new QLineEdit(this);

    m_dateNV = new QDateEdit(this);
    m_dateNV->setDateRange(QDate(1980,1,1),QDate(2000,12,31));
    m_dateNV->setCalendarPopup(true);                                         //hiển thị bảng lịch để chọn bằng click

    m_comboPhong = new QComboBox();
    QStringList strlistPhong;//={"RnD","Purchase","IQC"};
    strlistPhong.append("RnD");
    strlistPhong.append("Purchase");
    strlistPhong.append("IQC");
    m_comboPhong->addItems(strlistPhong);

    QGroupBox *grpboxGioitinh = new QGroupBox(this);
    m_rdbtnNam = new QRadioButton("Nam");
    //m_rdbtnNam->setChecked(true);
    m_rdbtnNu = new QRadioButton("Nữ");
    QHBoxLayout *layGioitinh = new QHBoxLayout();
    layGioitinh->addWidget(m_rdbtnNam);
    layGioitinh->addWidget(m_rdbtnNu);
    grpboxGioitinh->setLayout(layGioitinh);

    QGridLayout *gridNV = new QGridLayout();
    gridNV->addWidget(lbManv,0,0);
    gridNV->addWidget(m_lineeditManv,0,1);
    gridNV->addWidget(lbHeso,0,2);
    gridNV->addWidget(m_lineeditLuongnv,0,3);
    m_lineeditLuongnv->setValidator( new QIntValidator(0.0, 10.0, this) ); //cho phep heso chi dc nhap so 0.0-10.0
    gridNV->addWidget(lbTennv,1,0);
    gridNV->addWidget(m_lineeditTennv,1,1);
    gridNV->addWidget(lbGioitinh,1,2);
    gridNV->addWidget(grpboxGioitinh,1,3);
    gridNV->addWidget(lbNgaysinh,2,0);
    gridNV->addWidget(m_dateNV,2,1);
    gridNV->addWidget(lbPhongban,2,2);
    gridNV->addWidget(m_comboPhong,2,3);
    QGroupBox *groupNV = new QGroupBox("Thông tin nhân viên");
    groupNV->setLayout(gridNV);

    m_listNV = new QTableView();
    int nrow=1;
    int ncol=6;
    m_model = new QStandardItemModel(nrow,ncol);
    m_model->setHorizontalHeaderItem( 0, new QStandardItem( "Mã NV" ) );
    m_model->setHorizontalHeaderItem( 1, new QStandardItem( "Tên NV" ) );
    m_model->setHorizontalHeaderItem( 2, new QStandardItem( "Ngày sinh" ) );
    m_model->setHorizontalHeaderItem( 3, new QStandardItem( "Giới tính" ) );
    m_model->setHorizontalHeaderItem( 4, new QStandardItem( "Phòng ban" ) );
    m_model->setHorizontalHeaderItem( 5, new QStandardItem( "Hệ số lương" ) );

    m_listNV->setModel(m_model);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(groupNV);
    layout->addWidget(groupBtn);
    layout->addWidget(m_listNV);
    setLayout(layout);

    connect(btnAdd, SIGNAL(clicked(bool)),this, SLOT(addBtnClick()));
    connect(btnSearch, SIGNAL(clicked(bool)),this,SLOT(searchbtnClick()));
    connect(btnDel, SIGNAL(clicked(bool)),this,SLOT(deleteBtnClick()));
    connect(btnSort, SIGNAL(clicked(bool)),this,SLOT(sortBtnClick()));
    connect(btnExit, SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_listNV->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(tableClick()));
}

void QuanLyNhanVienUI::addBtnClick()
{
    if(m_lineeditManv->text()=="")
    {
        QMessageBox::warning(this, "Cảnh báo", "Bạn chưa nhập Mã nhân viên!");
        m_lineeditManv->setFocus();
    }
    else if(m_lineeditTennv->text()=="")
    {
        QMessageBox::warning(this, "Cảnh báo", "Bạn chưa nhập Tên nhân viên!");
        m_lineeditTennv->setFocus();
    }
    else if(m_lineeditLuongnv->text()=="")
    {
        QMessageBox::warning(this, "Cảnh báo", "Bạn chưa nhập Hệ số lương!");
        m_lineeditLuongnv->setFocus();
    }
    else if(Control::getInstace()->kiemtra(m_lineeditManv->text())>=0){
        QMessageBox::warning(this, "Cảnh báo", "Mã nhân viên đã tồn tai!"); //Tai sao hi nhap ma bang so laik xu ly kiem tra
        m_lineeditManv->setFocus();
    }
    else if(m_rdbtnNam->isChecked()== false && m_rdbtnNu->isChecked()== false)
    {
        QMessageBox::warning(this, "Cảnh báo", "Bạn chưa nhập Gioi tinh!");
    }
    else
    {
        QString manv = m_lineeditManv->text().trimmed();
        QString tennv = m_lineeditTennv->text();
        float heso = m_lineeditLuongnv->text().toFloat();
        QString ngaysinh = m_dateNV->date().toString("MM/dd/yyyy");
        QString phongban = m_comboPhong->currentText();
        QString gioitinh;
        if(m_rdbtnNam->isChecked()){
            gioitinh = "Nam";
        }
        else if(m_rdbtnNu->isChecked()){
            gioitinh = "Nu";
        }

        NhanVien *nhanvien = new NhanVien(manv, tennv, heso, gioitinh, ngaysinh, phongban);
        Control::getInstace()->arrNhanVien.append(nhanvien);
        soluong++;

        ssshowTable(Control::getInstace()->arrNhanVien, soluong);

        m_lineeditManv->setText("");
        m_lineeditTennv->setText("");
        m_lineeditLuongnv->setText("");
    }
}

void QuanLyNhanVienUI::searchbtnClick()
{
    m_newwin = new Searchwindow();
    m_newwin->setFixedSize(300,200);
    connect(m_newwin, SIGNAL(showResult(int)), this, SLOT(onShowResult(int)));
    m_newwin->show();
}

void QuanLyNhanVienUI::onShowResult(int row){
    //ssshowTable(Control::getInstace()->arrNhanVien, soluong);
    m_listNV->selectRow(row);
    m_listNV->focusWidget();
}

void QuanLyNhanVienUI::deleteBtnClick() //chua hieu code ???
{
    /*
    QItemSelection selection = m_listNV->selectionModel()->selection();
    QList<int> removeRows;
    foreach(QModelIndex index, selection.indexes()) {
        if(!removeRows.contains(index.row())) {
            removeRows.append(index.row());
        }
    }
    //loop through all selected rows
    for(int i=0;i<removeRows.count();++i)
    {
        //decrement all rows after the current - as the row-number will change if we remove the current
        for(int j=i;j<removeRows.count();++j) {
            if(removeRows.at(j) > removeRows.at(i)) {
                removeRows[j]--;
            }
        }
        //remove the selected row
        m_model->removeRows(removeRows.at(i), 1);
    }
*/

    int row = m_listNV->selectionModel()->currentIndex().row();  //get number of row Qtableview selection
    if(row<0){
        QMessageBox::warning(this, "Cảnh báo", "Chưa chọn nhân viên!");
    }
    else{
        Control::getInstace()->arrNhanVien.removeAt(row);
        soluong--;
    }
    ssshowTable(Control::getInstace()->arrNhanVien, soluong);
}

void QuanLyNhanVienUI::sortBtnClick()
{
    NhanVien *temp = new NhanVien();
    for(int i=0;i<Control::getInstace()->arrNhanVien.size()-1;i++){
        for(int j=i+1;j<Control::getInstace()->arrNhanVien.size();j++){
            if(Control::getInstace()->arrNhanVien.at(i)->getHeso()>Control::getInstace()->arrNhanVien.at(j)->getHeso()){
                temp = Control::getInstace()->arrNhanVien[i];
                Control::getInstace()->arrNhanVien[i] = Control::getInstace()->arrNhanVien[j];
                Control::getInstace()->arrNhanVien[j] = temp;
            }
        }
    }
    ssshowTable(Control::getInstace()->arrNhanVien, soluong);
}

void QuanLyNhanVienUI::changeBtnClick()
{
    int row = m_listNV->selectionModel()->currentIndex().row();

}

void QuanLyNhanVienUI::tableClick()
{
    int row = m_listNV->selectionModel()->currentIndex().row();  //get number of row Qtableview selection
    m_lineeditManv->setText(Control::getInstace()->arrNhanVien.at(row)->getManv());
    m_lineeditTennv->setText(Control::getInstace()->arrNhanVien.at(row)->getTennv());
    m_lineeditLuongnv->setText(QString::number(Control::getInstace()->arrNhanVien.at(row)->getHeso()));

    if(Control::getInstace()->arrNhanVien.at(row)->getGioitinh() == "Nam"){
        m_rdbtnNam->setChecked(true);
    }
    else if(Control::getInstace()->arrNhanVien.at(row)->getGioitinh() == "Nu"){
        m_rdbtnNu->setChecked(true);
    }

    if(Control::getInstace()->arrNhanVien.at(row)->getPhongban() == "RnD"){
        m_comboPhong->setCurrentText("RnD");
    }
    else if(Control::getInstace()->arrNhanVien.at(row)->getPhongban() == "Purchase"){
        m_comboPhong->setCurrentText("Purchase");
    }
    else if(Control::getInstace()->arrNhanVien.at(row)->getPhongban() == "IQC"){
        m_comboPhong->setCurrentText("IQC");
    }

    QDate Date;
    qDebug() << "date: " << Control::getInstace()->arrNhanVien.at(row)->getNgaySinh();
    Date = QDate::fromString(Control::getInstace()->arrNhanVien.at(row)->getNgaySinh());
    //Date = QDate::fromString(Control::getInstace()->arrNhanVien.at(row)->getNgaySinh(),"MM/dd/yyyy");
    m_dateNV->setDate(Date);
    //m_dateNV->setCurrentSection(arrNhanVien.at(row)->getNgaySinh());
}

void QuanLyNhanVienUI::ssshowTable(QList<NhanVien*> arr,int k)
{
    m_model->clear();
    m_model->setHorizontalHeaderItem( 0, new QStandardItem( "Mã NV" ) );
    m_model->setHorizontalHeaderItem( 1, new QStandardItem( "Tên NV" ) );
    m_model->setHorizontalHeaderItem( 2, new QStandardItem( "Ngày sinh" ) );
    m_model->setHorizontalHeaderItem( 3, new QStandardItem( "Giới tính" ) );
    m_model->setHorizontalHeaderItem( 4, new QStandardItem( "Phòng ban" ) );
    m_model->setHorizontalHeaderItem( 5, new QStandardItem( "Hệ số lương" ) );
    for(int n=0; n<k; n++){
        QStandardItem *r00 = new QStandardItem(QString(arr.at(n)->getManv()));
        m_model->setItem(n,0,r00);
        QStandardItem *r01 = new QStandardItem(QString(arr.at(n)->getTennv()));
        m_model->setItem(n,1,r01);
        QStandardItem *r05 = new QStandardItem(QString::number(arr.at(n)->getHeso()));
        m_model->setItem(n,5,r05);
        QStandardItem *r02 = new QStandardItem(QString(arr.at(n)->getNgaySinh()));
        m_model->setItem(n,2,r02);
        QStandardItem *r04 = new QStandardItem(QString(arr.at(n)->getPhongban()));
        m_model->setItem(n,4,r04);
        QStandardItem *r03 = new QStandardItem(QString(arr.at(n)->getGioitinh()));
        m_model->setItem(n,3,r03);
    }
}
