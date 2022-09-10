#include "connectmysql.h"



connectMySql::connectMySql(QString db)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("MySql");
    db.setUserName("root");
    db.setPassword("40333129");
//    bool t_bIsOk = db.open();
//    if(t_bIsOk)
//    {
//        qDebug()<<"link success";
//        l.show();
//        return a.exec();
//    }
//    else     //数据库连接失败则不显示窗口
//    {
//        qDebug()<<"link failure because "<<db.lastError().text();

//        return a.exec();
//    }
}
