#include "rankwindow.h"
#include "ui_rankwindow.h"
#include<QDebug>

RankWindow::RankWindow(QString name,QWidget *parent) :
    QMainWindow(parent),user_name(name),
    ui(new Ui::RankWindow)
{
    ui->setupUi(this);
    setWindowTitle("排行榜");
    ui->ShowInfotableView->setSelectionMode(QAbstractItemView::SingleSelection); //单次选择
    ui->ShowInfotableView->setSelectionBehavior(QAbstractItemView::SelectItems); //选中一个item

    recordsModel=new QStandardItemModel();

    ui->ShowInfotableView->setModel(recordsModel);

//    connect(ui->ShowInfotableView->itemDelegate(),&QAbstractItemDelegate::closeEditor,
//            this,&RankWindow::)

    connect(ui->action_my_low,&QAction::triggered,this,&RankWindow::showMyLow);
    connect(ui->action_my_middle,&QAction::triggered,this,&RankWindow::showMyMiddle);
    connect(ui->action_my_high,&QAction::triggered,this,&RankWindow::showMyHigh);

    connect(ui->action_global_low,&QAction::triggered,this,&RankWindow::showGlobalLow);
    connect(ui->action_global_middle,&QAction::triggered,this,&RankWindow::showGlobalMiddle);
    connect(ui->action_global_high,&QAction::triggered,this,&RankWindow::showGlobalHigh);



}

RankWindow::~RankWindow()
{
    delete ui;
}

//void RankWindow::on_ShowInfotableView_changed()
//{
//    QModelIndex index = ui->ShowInfotableView->currentIndex();

//}





void RankWindow::showMyLow()
{
//    qDebug()<<"test111111";
//    m_iCurTable=1;
    recordsModel->clear();
    recordsModel->setColumnCount(3);

    QStringList templist;
    templist.append("序号");
    templist.append("用时");
    templist.append("日期");

    recordsModel->setHorizontalHeaderLabels(templist);//设置水平标题

    int t_nRowCount=8;//行数
    recordsModel->setRowCount(t_nRowCount);//设置行数

    QStandardItem *aTempItem;
    QString tempStr;
    QSqlQuery query;
    query.prepare("select * from records where game_level=0 and user_name ="
                  ":user_name order by game_time");
    query.bindValue(":user_name",user_name);
    query.exec();
//    QString s="select * from records where game_level=0 and user_name ="+/*user_name*/"张三";
//    query.exec(s);
//    QString t="select *from records where game_level=0";
//    query.exec(t);
    int i=0;
    while(query.next())
    {
        tempStr=QString::number(query.value(0).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,0,aTempItem);

        qDebug()<<"test2222222"<<query.value(0);

        tempStr=QString::number(query.value(3).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,1,aTempItem);

        tempStr=query.value(4).toString();
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,2,aTempItem);
        i++;
    }



}

void RankWindow::showMyMiddle()
{
    recordsModel->clear();
    recordsModel->setColumnCount(3);

    QStringList templist;
    templist.append("序号");
    templist.append("用时");
    templist.append("日期");

    recordsModel->setHorizontalHeaderLabels(templist);//设置水平标题

    int t_nRowCount=8;//行数
    recordsModel->setRowCount(t_nRowCount);//设置行数

    QStandardItem *aTempItem;
    QString tempStr;
    QSqlQuery query;
    query.prepare("select * from records where game_level=1 and user_name ="
                  ":user_name order by game_time");
    query.bindValue(":user_name",user_name);
    query.exec();
//    QString s="select * from records where game_level=0 and user_name ="+/*user_name*/"张三";
//    query.exec(s);
//    QString t="select *from records where game_level=0";
//    query.exec(t);
    int i=0;
    while(query.next())
    {
        tempStr=QString::number(query.value(0).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,0,aTempItem);

        qDebug()<<"test2222222"<<query.value(0);

        tempStr=QString::number(query.value(3).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,1,aTempItem);

        tempStr=query.value(4).toString();
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,2,aTempItem);
        i++;
    }

}

void RankWindow::showMyHigh()
{
    recordsModel->clear();
    recordsModel->setColumnCount(3);

    QStringList templist;
    templist.append("序号");
    templist.append("用时");
    templist.append("日期");

    recordsModel->setHorizontalHeaderLabels(templist);//设置水平标题

    int t_nRowCount=8;//行数
    recordsModel->setRowCount(t_nRowCount);//设置行数

    QStandardItem *aTempItem;
    QString tempStr;
    QSqlQuery query;
    query.prepare("select * from records where game_level=2 and user_name ="
                  ":user_name order by game_time");
    query.bindValue(":user_name",user_name);
    query.exec();
//    QString s="select * from records where game_level=0 and user_name ="+/*user_name*/"张三";
//    query.exec(s);
//    QString t="select *from records where game_level=0";
//    query.exec(t);
    int i=0;
    while(query.next())
    {
        tempStr=QString::number(query.value(0).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,0,aTempItem);

        qDebug()<<"test2222222"<<query.value(0);

        tempStr=QString::number(query.value(3).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,1,aTempItem);

        tempStr=query.value(4).toString();
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,2,aTempItem);
        i++;
    }
}

void RankWindow::showGlobalLow()
{
    recordsModel->clear();
    recordsModel->setColumnCount(3);

    QStringList templist;
    templist.append("序号");
    templist.append("用户名");
    templist.append("用时");
    templist.append("日期");

    recordsModel->setHorizontalHeaderLabels(templist);//设置水平标题

    int t_nRowCount=8;//行数
    recordsModel->setRowCount(t_nRowCount);//设置行数

    QStandardItem *aTempItem;
    QString tempStr;
    QSqlQuery query;
    query.prepare("select * from records where game_level=0 order by game_time");
//    query.bindValue(":user_name",user_name);
    query.exec();
//    QString s="select * from records where game_level=0 and user_name ="+/*user_name*/"张三";
//    query.exec(s);
//    QString t="select *from records where game_level=0";
//    query.exec(t);
    int i=0;
    while(query.next())
    {
        tempStr=QString::number(query.value(0).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,0,aTempItem);

//        qDebug()<<"test2222222"<<query.value(0);
        tempStr=query.value(1).toString();
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,1,aTempItem);

        tempStr=QString::number(query.value(3).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,2,aTempItem);

        tempStr=query.value(4).toString();
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,3,aTempItem);
        i++;
    }
}

void RankWindow::showGlobalMiddle()
{
    recordsModel->clear();
    recordsModel->setColumnCount(3);

    QStringList templist;
    templist.append("序号");
    templist.append("用时");
    templist.append("日期");

    recordsModel->setHorizontalHeaderLabels(templist);//设置水平标题

    int t_nRowCount=8;//行数
    recordsModel->setRowCount(t_nRowCount);//设置行数

    QStandardItem *aTempItem;
    QString tempStr;
    QSqlQuery query;
    query.prepare("select * from records where game_level=1 order by game_time");
//    query.bindValue(":user_name",user_name);
    query.exec();
//    QString s="select * from records where game_level=0 and user_name ="+/*user_name*/"张三";
//    query.exec(s);
//    QString t="select *from records where game_level=0";
//    query.exec(t);
    int i=0;
    while(query.next())
    {
        tempStr=QString::number(query.value(0).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,0,aTempItem);

        //        qDebug()<<"test2222222"<<query.value(0);
                tempStr=query.value(1).toString();
                aTempItem = new QStandardItem(tempStr);
                recordsModel->setItem(i,1,aTempItem);

                tempStr=QString::number(query.value(3).toInt());
                aTempItem = new QStandardItem(tempStr);
                recordsModel->setItem(i,2,aTempItem);

                tempStr=query.value(4).toString();
                aTempItem = new QStandardItem(tempStr);
                recordsModel->setItem(i,3,aTempItem);
                i++;
    }
}

void RankWindow::showGlobalHigh()
{
    recordsModel->clear();
    recordsModel->setColumnCount(3);

    QStringList templist;
    templist.append("序号");
    templist.append("用时");
    templist.append("日期");

    recordsModel->setHorizontalHeaderLabels(templist);//设置水平标题

    int t_nRowCount=8;//行数
    recordsModel->setRowCount(t_nRowCount);//设置行数

    QStandardItem *aTempItem;
    QString tempStr;
    QSqlQuery query;
    query.prepare("select * from records where game_level=2 order by game_time");
//    query.bindValue(":user_name",user_name);
    query.exec();
//    QString s="select * from records where game_level=0 and user_name ="+/*user_name*/"张三";
//    query.exec(s);
//    QString t="select *from records where game_level=0";
//    query.exec(t);
    int i=0;
    while(query.next())
    {
        tempStr=QString::number(query.value(0).toInt());
        aTempItem = new QStandardItem(tempStr);
        recordsModel->setItem(i,0,aTempItem);

        //        qDebug()<<"test2222222"<<query.value(0);
                tempStr=query.value(1).toString();
                aTempItem = new QStandardItem(tempStr);
                recordsModel->setItem(i,1,aTempItem);

                tempStr=QString::number(query.value(3).toInt());
                aTempItem = new QStandardItem(tempStr);
                recordsModel->setItem(i,2,aTempItem);

                tempStr=query.value(4).toString();
                aTempItem = new QStandardItem(tempStr);
                recordsModel->setItem(i,3,aTempItem);
                i++;
    }
}
