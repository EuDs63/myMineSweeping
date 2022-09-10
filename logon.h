#ifndef LOGON_H
#define LOGON_H

#include <QMainWindow>
#include<QMessageBox>
#include<QDebug>
#include<QSqlQuery>
#include"rigister.h"
#include"GameWindow.h"

namespace Ui {
class logon;
}

class GameWindow;

class logon : public QMainWindow
{
    Q_OBJECT

public:
    explicit logon(QWidget *parent = nullptr);
    ~logon();
//    void text()
//    {
//      qDebug()<<"text";

//    }

private:
    Ui::logon *ui;
    QString a;

signals:


private slots:
    void on_btn_Login_clicked();  //登录按钮被点击
    void on_btn_Rigister_clicked(); //注册按钮被点击
};

#endif // LOGON_H
