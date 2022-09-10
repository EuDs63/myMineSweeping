#include "rigister.h"
#include "ui_rigister.h"

Rigister::Rigister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rigister)
{
    ui->setupUi(this);  //注意：要先创建
    setWindowTitle("注册");
    this->setWindowModality(Qt::ApplicationModal);//模态窗口
    ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit_2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit_3->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->textEdit_4->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    connect(ui->pushButton_Confirm,SIGNAL(clicked()),this,SLOT(on_btn_Register_clicked()));
}

Rigister::~Rigister()
{
    delete ui;
}

void Rigister::on_btn_Register_clicked()
{
    QString t_sUser_Name=ui->lineEdit_Name->text();//用户名
    QSqlQuery query;
    query.prepare("select user_name from users where user_name=:user_name");
    query.bindValue(":user_name",t_sUser_Name);
    query.exec();
    if(query.next())
    {
        //库中已有用户名
        QMessageBox::information(this,"Error","用户名已存在！",QMessageBox::Ok);
    }
    else//判断密码是否输入一致
    {
        if(!(ui->lineEdit_Password->text()==ui->lineEdit_Password2->text()))
        {
            //两次密码输入不一致
            QMessageBox::information(this,"Error","两次密码输入不一致",QMessageBox::Ok);
        }
        else
        {
            QString t_sUser_Password=ui->lineEdit_Password->text();
            //选择水平
            QButtonGroup *bg=new QButtonGroup(this);
            bg->addButton(ui->radioButton_a,0);//入门
            bg->addButton(ui->radioButton_b,1);//进阶
            bg->addButton(ui->radioButton_c,2);//高手


            int t_iUser_Level=bg->checkedId();

//            QDateTime::currentDateTime()

            query.prepare("insert into users(user_name,user_code,user_level)"
                          "values(:user_name,:user_code,:user_level)");
            query.bindValue(":user_name",t_sUser_Name);
            query.bindValue(":user_code",t_sUser_Password);
            query.bindValue(":user_level",t_iUser_Level);

            query.exec();
            QMessageBox::information(this,"Information","注册成功",QMessageBox::Ok);
            this->close();
//            logon *a=new logon;
//           a->show();
        }
    }



}
