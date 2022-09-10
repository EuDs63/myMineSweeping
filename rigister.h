#ifndef RIGISTER_H
#define RIGISTER_H

#include <QWidget>
#include<QMessageBox>
#include<QDateTime>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QButtonGroup>
#include<QDateTime>
//#include"logon.h"


namespace Ui {
class Rigister;
}

class Rigister : public QWidget
{
    Q_OBJECT

public:
    explicit Rigister(QWidget *parent = nullptr);
    ~Rigister();

private:
    Ui::Rigister *ui;

private slots:
    void on_btn_Register_clicked(); //注册按钮被点击
};

#endif // RIGISTER_H
