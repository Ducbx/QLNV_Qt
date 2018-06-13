#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H
#include<QWidget>
#include<QDialog>
#include<QComboBox>
#include<QStringList>
#include<QLineEdit>



class Searchwindow :public QDialog
{
    Q_OBJECT
public:
    Searchwindow(QWidget *parent=0);

signals:
    void showResult(int row);

private slots:
    void btnSearchClick();
private:
    QComboBox *comboType;
    QLineEdit *lineeditSearch; //vie ham get
};

#endif // SEARCHWINDOW_H
