#include "data.h"

Data::Data()
{

}
int kiemtraNV(QList<NhanVien*> arr, QString manv)
{
    for(int i =0; i<arr.size(); i++){
        if(arr.at(i)->getManv()== manv)return 1;
        else return 0;
    }
}
