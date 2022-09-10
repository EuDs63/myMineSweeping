#include "mysql.h"
#include"configfile.h"
#include<QApplication>

mySql::mySql()
{

//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    qDebug()<<"software path ="<<QApplication::applicationDirPath();
    QString qStrFileName=(/*QApplication::applicationDirPath()+*/
                          "D:/QtLearning/mySql_learning2/config/databaseInfo.cfg");//这里我直接指定了文件的路径，实际操作不推荐
    configFile cfg;
    if(!cfg.fileName(qStrFileName))
        qDebug()<<"文件不存在:"<<qStrFileName;
//    QString strArray[5];
//    strArray[0] = cfg.get("database","HostName").toString();
//    strArray[1] = cfg.get("database","Port").toString();
//    strArray[2] = cfg.get("database","UserName").toString();
//    strArray[3] = cfg.get("database","Password").toString();
//    strArray[4] = cfg.get("database","DatabaseName").toString();
//    for(int i=0;i<5;i++)
//        qDebug()<<strArray[i];

    db.setHostName(cfg.get("database","HostName").toString());
    db.setPort(cfg.get("database","Port").toInt());
    db.setDatabaseName(cfg.get("database","DatabaseName").toString());
    db.setUserName(cfg.get("database","UserName").toString());
    db.setPassword(cfg.get("database","Password").toString());
    m_bIsOk=db.open();
}//连接数据库

void mySql::showMyTables()
{
    QStringList tables = db.tables();
    foreach(QString table, tables)
        qDebug()<<"tables in database:"<<table;
}

void mySql::showUserInformation()
{
    QSqlQuery result =db.exec("select *from users");
    while(result.next())
    {
        qDebug()<<"user_id:"<<result.value("user_id").toInt();
        qDebug()<<"user_name"<<result.value("user_name").toString();
        qDebug()<<"user_code"<<result.value("user_code").toString();
    }
}

