#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>

#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>

class mySql
{
public:
    mySql();


    void showMyTables();//查询并打印数据库中所有表的名称

    void showUserInformation();//查询并打印数据库中存储的用户信息


public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool m_bIsOk;//判断数据库是否成功连接

};

#endif // MYSQL_H
