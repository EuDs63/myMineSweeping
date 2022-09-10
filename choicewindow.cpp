#include "choicewindow.h"
#include "ui_choicewindow.h"

ChoiceWindow::ChoiceWindow(GameWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    setWindowTitle("选项");

    //连接各部件

    //1.确认按钮
    connect(ui->Button_Apply,&QPushButton::clicked,[=]()
    {
        //保存默认的信息
        if(ui->radioButton_default->isChecked())
        {
            saveDefault(parent);
        }
        //保存用户自定义的信息
        if(ui->radioButton_custom->isChecked())
        {
            saveCustom(parent);
        }
    });

    //2.应用按钮
    connect(ui->Button_Apply,&QPushButton::clicked,[=]()
    {
        //保存默认的信息,关闭窗口
        if(ui->radioButton_default->isChecked())
        {
            saveDefault(parent);
            this->close();
        }

        //保存用户自定义的信息,如果信息没出错，则关闭窗口
        else if(ui->radioButton_custom->isChecked())
        {
            if(saveCustom(parent))
                this->close();
        }
    });

    //取消按钮,直接关闭窗口
    connect(ui->Button_Cancel,&QPushButton::clicked,[=]()
    {
        this->close();
    });

    //选择自定义时，禁用默认按钮
    connect(ui->radioButton_custom,&QRadioButton::clicked,[=]()
    {
        ui->radioButton_default_highLevel->setDisabled(true);
        ui->radioButton_default_midLevel->setDisabled(true);
        ui->radioButton_default_lowLevel->setDisabled(true);

        ui->text_choice_height->setDisabled(false);
        ui->text_choice_width->setDisabled(false);
        ui->text_choice_mineNumber->setDisabled(false);
    });

    //选择默认时，禁用自定义按钮
    connect(ui->radioButton_default,&QRadioButton::clicked,[=]()
    {
        ui->radioButton_default_highLevel->setDisabled(false);
        ui->radioButton_default_midLevel->setDisabled(false);
        ui->radioButton_default_lowLevel->setDisabled(false);

        ui->text_choice_height->setDisabled(true);
        ui->text_choice_width->setDisabled(true);
        ui->text_choice_mineNumber->setDisabled(true);
    });
}

ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}

void ChoiceWindow::saveDefault(GameWindow *parent)
{
    if(ui->radioButton_default_highLevel->isChecked())//高级
    {
        parent->setHeight(30);
        parent->setWidth(16);
        parent->setMineNumber(99);
    }
    else if(ui->radioButton_default_midLevel->isChecked())//中级
    {
        parent->setHeight(16);
        parent->setWidth(16);
        parent->setMineNumber(40);
    }
    else//初级
    {
        parent->setHeight(10);
        parent->setWidth(10);
        parent->setMineNumber(10);
    }
    parent->initAll();
}

bool ChoiceWindow::saveCustom(GameWindow *parent)
{
    //从输入框中读取数据
    int h = ui->text_choice_height->text().toInt();
    int w = ui->text_choice_width->text().toInt();
    int m = ui->text_choice_mineNumber->text().toInt();

    if((h>0 && h<=40) && (w>0 && w<= 40))
    {//尺寸符合要求
        if(m<0 || m>(h*m))//雷数过少或过多
        {
             QMessageBox::critical(this,"Error","您输入的雷数有误，应用失败",QMessageBox::Ok);
             return false;
        }
        else
        {
            parent->setHeight(h);
            parent->setWidth(w);
            parent->setMineNumber(m);
            parent->initAll();
            return true;
        }

    }
    else
    {
        QMessageBox::critical(this,"Error","您输入的尺寸有误，应用失败",QMessageBox::Ok);
        return false;
    }
}



