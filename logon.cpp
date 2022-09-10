#include "logon.h"
#include "ui_logon.h"
#include"GameWindow.h"
#include"choicewindow.h"//测试

logon::logon(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::logon)
{

    ui->setupUi(this);
    setWindowTitle("登录");
    //this->resize(500,250);
//    ui->checkBox_isShow->
    //this->setWindowFlags(this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
//    if(ui->radioButton_isShow->isChecked())
//    {
//        ui->lineEdit_code->setEchoMode(QLineEdit::Normal);
//    }
//    else
//    {
//        ui->lineEdit_code->setEchoMode(QLineEdit::Password);
//    }
    //实现可根据用户选择，实时切换密码的显示方式
    ui->lineEdit_code->setEchoMode(QLineEdit::Password);//初始时设置为password模式

    connect(ui->radioButton_isShow,&QRadioButton::clicked,[=]()
    {
        if(ui->lineEdit_code->echoMode()==QLineEdit::Password)
        {
            ui->lineEdit_code->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            ui->lineEdit_code->setEchoMode(QLineEdit::Password);
        }
    });//radioButton被点击则切换成另一种echomode

//    connect(ui->radioButton_isShow,&QRadioButton::toggle,[=]()
//    {
//        ui->lineEdit_code->setEchoMode(QLineEdit::Password);
//    });


//    connect(ui->checkBox_isShow,&QCheckBox::c)

    connect(ui->button_Login,SIGNAL(clicked()),this,SLOT(on_btn_Login_clicked()));
    //connect(ui->button_Register,SIGNAL(clicked()),this,SLOT(on_btn_Register_clicked()));

    connect(ui->button_Register,&QPushButton::clicked,[=]()
    {
        on_btn_Rigister_clicked();
//        Rigister *r=new Rigister;
////            r->setWindowModality(Qt::WindowModal);
////            r->setAttribute(Qt::WA_DeleteOnClose);
//        r->show();
    });
}

logon::~logon()
{
    delete ui;
}

void logon::on_btn_Login_clicked()
{
    QString t_sUserName=ui->lineEdit_Name->text(); //用户名
    QString t_sPassword=ui->lineEdit_code->text(); //密码

    if(t_sUserName==""||t_sPassword=="")
    {
        QMessageBox::information(this,"ERROR","输入不能为空",QMessageBox::Ok);
    }
    else //用户名和密码都有输入
    {   //疑惑，我这里并没有连接数据库，为什么程序能跑呢？  //默认的
        QSqlQuery query;
        query.prepare("select user_name,user_code from users where user_name=:user_name and user_code=:user_code");
        query.bindValue(":user_name",t_sUserName);
        query.bindValue(":user_code",t_sPassword);//名称绑定
        query.exec();
        if(!query.next())//用户名或密码错误
           {

             QMessageBox::information(this,"警告","用户名或密码错误！",QMessageBox::Ok);
           }
           else//登录成功，跳转至下一界面
           {
             QMessageBox::information(this,"提醒","登录成功！",QMessageBox::Ok);
             GameWindow*g=new GameWindow(t_sUserName);
             g->show();
              this->close();
            }
    }


}

void logon::on_btn_Rigister_clicked()
{

    Rigister *r=new Rigister;
    r->setAttribute(Qt::WA_DeleteOnClose);
    r->show();

//    ChoiceWindow*c=new ChoiceWindow;
//    c->setWindowModality(Qt::WindowModal);
//    c->setAttribute(Qt::WA_DeleteOnClose);
//    c->show();

}



