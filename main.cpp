#include"logon.h"
#include"mysql.h"
#include <QApplication>
#include<QMessageBox>
#include<QSqlError>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    logon l;
//    l.text();

    mySql s;
    if(s.m_bIsOk)
    {
        qDebug()<<"link success";
        l.show();
//        s.showMyTables();
//        s.showUserInformation();
        return a.exec();
    }
    else     //数据库连接失败则不显示窗口
    {
        qDebug()<<"link failure because "<<s.db.lastError().text();
        QMessageBox::information(0,"ERROR","无法连接到数据库",QMessageBox::Ok);
        return a.exec();
    }






}
