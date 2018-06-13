#include "control.h"
#include<QStandardItemModel>

static Control* instance = NULL;

Control::Control()
{

}

Control *Control::getInstace()
{
    if(instance == NULL){
        instance = new Control();
    }
    return instance;
}

int Control::kiemtra(QString manv)
{
    for(int i =0; i<arrNhanVien.size(); i++){
        if(arrNhanVien.at(i)->getManv()== manv.trimmed())return i;
    }
    return -1;
}
