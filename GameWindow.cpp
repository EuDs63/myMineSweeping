#include "GameWindow.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(QString name,QWidget *parent) :
    QMainWindow(parent),user_name(name),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    setWindowTitle("扫雷");

    initAll();

    //一.对窗口中的各个控件进行连接


    //（一）开始菜单栏

    //1.1重新开始
    connect(ui->action_Restart,&QAction::triggered,[=]()
    {
        initAll();
    });

    //1.2选项
    connect(ui->action_Option,&QAction::triggered,[=]()
    {
        ChoiceWindow*c=new ChoiceWindow(this);
        c->setWindowModality(Qt::WindowModal);
        c->setAttribute(Qt::WA_DeleteOnClose);
        c->show();
    });

    //1.3排行榜
    connect(ui->action_Rank,&QAction::triggered,[=]()
    {
        RankWindow*r=new RankWindow(user_name,this);
        r->setWindowModality(Qt::WindowModal);
        r->setAttribute(Qt::WA_DeleteOnClose);
        r->show();
    });

    //(二）帮助菜单栏

    //2.1关于
    connect(ui->action_about,&QAction::triggered,[=]()
    {
        AboutWindow*a=new AboutWindow(this);
        a->setWindowModality(Qt::WindowModal);
        a->setAttribute(Qt::WA_DeleteOnClose);
        a->show();
    });

    //2.2帮助
    connect(ui->action_Method,&QAction::triggered,[=]()
    {
        HelpWindow*h=new HelpWindow(this);
        h->setWindowModality(Qt::WindowModal);
        h->setAttribute(Qt::WA_DeleteOnClose);
        h->show();
    });




    //中央按钮
    connect(ui->Button_certral,&QPushButton::clicked,[=]()
    {
        initAll();
    });//点击中央按钮则初始化游戏
    connect(ui->Button_certral,&QPushButton::pressed,[=]()
    {
        ui->Button_certral->setIcon(QIcon(":/prefix1/image/jinya.png"));
    });//按住中央按钮时
    connect(ui->Button_certral,&QPushButton::released,[=]()
    {
        ui->Button_certral->setIcon(QIcon(":/prefix1/image/xixi.png"));
    });//释放中央按钮时

    //lcd_TimeCount
    ui->lcd_TimeCount->setDigitCount(3);//显示三位数
    ui->lcd_TimeCount->setStyleSheet("border: 1px solid green; color: red; background: black;");//调整显示风格
    timer=new QTimer(this);
    timer->start(1000);

    //lcd_MineCount
    ui->lcd_MineCount->setDigitCount(3);
    ui->lcd_MineCount->setStyleSheet("border: 1px solid green; color: red; background: black;");//调整显示风格
    ui->lcd_MineCount->display(m_nMineCount);


//    initAll();
}

GameWindow::~GameWindow()
{
    delete ui;
}

//初始化雷表
void GameWindow::initMineTable()
{
    m_nWinCount=m_nHeight*m_nWidth-m_nMineNumber;
    m_vMineTabel.clear();

    //雷表的尺寸在map的尺寸上加2
    int h=m_nHeight+2;
    int w=m_nWidth+2;

    int m=m_nMineNumber;

    //先全部赋值为0
    for(int i=0;i<h;i++)
    {
        QVector<int>temp;
        for(int j=0;j<w;j++)
        {
            temp.push_back(0);
        }
        m_vMineTabel.push_back(temp);
    }

    //设置雷的位置
    QTime time;
    srand(time.msec()+time.second());
    while(m!=0)
    {
        int x = 1+rand()%m_nHeight;
        int y = 1+rand()%m_nWidth;
        if(m_vMineTabel[x][y]==0)
        {
            m_vMineTabel[x][y]=-1;  //-1代表雷
            --m;
        }
    }

    //设定其他格子上的数字
    for(int i=1;i<h-1;i++)
    {
        for(int j=1;j<w-1;j++)
        {
            if(m_vMineTabel[i][j]==0)
            {
                m_vMineTabel[i][j]=aroundCount(i,j);
            }
        }
    }
}

int GameWindow::aroundCount(int i,int j)
{
    int t_nCount=0;
    for(int x=i-1;x<i+2;x++)
    {
        for(int y=j-1;y<j+2;y++)
        {
            if(m_vMineTabel[x][y]==-1)
                ++t_nCount;
        }
    }//遍历周围八个格子
    return t_nCount;
}



//初始化游戏
void GameWindow::initAll()
{
    //ui->setupUi(this);

    //对中央按钮初始化图像
    ui->Button_certral->setIcon(QIcon(":/prefix1/image/xixi.png"));

    ui->lcd_MineCount->setDigitCount(3);
    ui->lcd_MineCount->setStyleSheet("border: 1px solid green; color: red; background: black;");//调整显示风格
    ui->lcd_MineCount->display(m_nMineCount);


    //初始化雷表
    initMineTable();

    //初始化时间
    sec=0;

    //开始计时
    m_bIsTimeCount=true;

    //初始化雷数
    m_nMineCount=m_nMineNumber;

    //清理掉之前开辟按钮所用的空间
    if(m_vMap.size()!=0)
    {
        for(int i=0;i<m_vMap.size();i++)
        {
            for(int j=0;j<m_vMap[0].size();j++)
            {
                if(m_vMap[i][j]!=nullptr)
                    delete m_vMap[i][j];
            }
        }
    }
    m_vMap.clear();

    //设置窗口大小
    setFixedSize(40+20*m_nHeight,100+20*m_nWidth);

    //初始化map,建立数组
    for(int i=0;i<m_nHeight;i++)
    {
        QVector<myPushButton*>t;
        for(int j=0;j<m_nWidth;j++)
        {
            myPushButton *temp=new myPushButton(this);
            temp->resize(20,20);   //设置按钮大小
            temp->move(20+20*i,90+20*j);//设置按钮位置
            t.push_back(temp);
        }
        m_vMap.push_back(t);
    }

    //将map与minetable联系起来
    for(int i=0;i<m_vMap.size();i++)
    {
//         qDebug()<<"建立行数i:"<<i;
        for(int j=0;j<m_vMap[0].size();j++)
        {
            m_vMap[i][j]->show();//显示按钮
//            qDebug()<<j;

            //建立联系

            connect(m_vMap[i][j],&myPushButton::leftRightPressed,[=]()
            {
                if(m_vMineTabel[i+1][j+1]==-2)//-2表示已被打开
                {
                    for(int x=i-1;x<i+2;x++)
                    {
                        for(int y=j-1;y<j+2;y++)
                        {
                            if(y>=0&&x>=0&&x<m_nHeight&&y<m_nWidth)//不超出范围
                            {
                                if(m_vMineTabel[x+1][y+1]>-2&&m_vMineTabel[x+1][y+1]<9)
                                    m_vMap[x][y]->setIcon(QIcon(":/prefix1/image/blank.png"));
                                //按住时，周围未打开及未标记的按钮会显示为blank
                            }
                        }
                    }
                }
                gameOver(true);
            });//同时按下

            connect(m_vMap[i][j],&myPushButton::leftRightReleased,[=]()
            {
               ui->Button_certral->setIcon(QIcon(":/prefix1/image/xixi.png"));
               int t_nMineCount=0;
               int t_nFlagCount=0;
               int t_nQuestionCount=0;

               //对周围八个格子进行遍历
               for(int x= i-1; x<i+2;x++)
               {
                   for(int y = j-1; y<j+2; y++)
                   {
                       if(y>=0&&x>=0&&x<m_nHeight&&m_nWidth)//不超出范围
                       {
                           if(m_vMineTabel[x+1][y+1]==-1)
                               ++t_nMineCount;
                           if(m_vMineTabel[x+1][y+1] >= 9 && m_vMineTabel[x+1][y+1] <= 80 && m_vMineTabel[x+1][y+1] == -10)
                               ++t_nQuestionCount;   // 9：标？0号格   -10：标？雷格   10,20,30，…… 80：标？周围有雷格
                           if(m_vMineTabel[x+1][y+1] >= 99)// 99:标旗0号格； -100：标旗雷格；100,200,300……800：标旗周围有雷格
                               ++t_nFlagCount;
                           if(m_vMineTabel[x+1][y+1]>-2&&m_vMineTabel[x+1][y+1]<9)
                               m_vMap[x][y]->setIcon(QIcon(""));
                       }
                   }
               }

               //开始判定
               if(t_nFlagCount!=0&&t_nMineCount!=0)//有标旗，也有标雷，但雷并没有全部标出
               {
                   gameOver(false);//游戏结束
               }
               else if(t_nFlagCount==0&&t_nMineCount==0&&t_nQuestionCount==0)
               {
                   for(int x= i-1; x<i+2; ++x)
                   {
                       for(int y = j-1; y<j+2; ++y)
                       {
                           if(y>=0 && x>=0 && x< m_nHeight && y<m_nWidth)//在界限范围内
                           {
                               if(m_vMineTabel[x+1][y+1] > -2 && m_vMineTabel[x+1][y+1] < 9)
                               {
                                   int count = 10;
                                   mineDfs(x,y,count);
                               }
                           }
                       }
                   }
               }
               gameOver(true);

            });//同时抬起

            connect(m_vMap[i][j],&myPushButton::leftChecked,[=]()
            {
                ui->Button_certral->setIcon(QIcon(":/prefix1/image/xiaxia.png"));
            });//左键按下

            connect(m_vMap[i][j],&myPushButton::leftReleased,[=]()
            {
                ui->Button_certral->setIcon(QIcon(":/prefix1/image/xixi.png"));
                if(m_bIsTimeCount)
                {
                    connect(timer,&QTimer::timeout,[=]()
                    {
                        sec++;
                        ui->lcd_TimeCount->display(sec);//开始计时
                    });
                    m_bIsTimeCount=false;
                }
                if(m_vMineTabel[i+1][j+1]==-1)
                {
                    m_vMap[i][j]->setIcon(QIcon(":/prefix1/image/mine.png"));
                    gameOver(false);
                }
                else if(m_vMineTabel[i+1][j+1]>=0&&m_vMineTabel[i+1][j+1]<9)
                {
                    int count=10;
                    mineDfs(i,j,count);
                }
                gameOver(true);
            });//左键释放

            //建立鼠标右键与按钮的联系
            //右键需要标记两个状态，flag和question
            //注意：-1有雷，-2已打开
            connect(m_vMap[i][j],&myPushButton::rightChecked,[=]()
            {
                if(m_bIsTimeCount)//开始计时
                {
                    connect(timer,&QTimer::timeout,[=]()
                    {
                        sec++;
                        ui->lcd_TimeCount->display(sec);
                    });
                    m_bIsTimeCount=false;
                }

                //右击无状态的格子,转换为flag态;  99:标旗0号格； -100：标旗雷格；100,200,300……800：标旗周围有雷格
                if(m_vMineTabel[i+1][j+1] > -2 && m_vMineTabel[i+1][j+1] < 9)
                {
                    --m_nMineCount;
                    ui->lcd_MineCount->display(m_nMineCount);
                    m_vMap[i][j]->setIcon(QIcon(":/prefix1/image/flag.png"));
                    if(m_vMineTabel[i+1][j+1] == 0)//如果右击的格子自身和周围没有雷,设为99
                    {
                        m_vMineTabel[i+1][j+1] = 99;
                    }
                    else
                    {
                        m_vMineTabel[i+1][j+1] *= 100;//有的话则*100，即被标旗的格子如果有雷则为-100
                    }
                }
                //右击flag态的格子，转换为question态   9：标？0号格   -10：标？雷格   10,20,30，…… 80：标？周围有雷格
                else if(m_vMineTabel[i+1][j+1]==-100||m_vMineTabel[i+1][j+1]>90)//判断是否标旗
                {
                    ++m_nMineCount;
                    ui->lcd_MineCount->display(m_nMineCount);
                     m_vMap[i][j]->setIcon(QIcon(":/prefix1/image/question.png"));
                     if(m_vMineTabel[i+1][j+1]==99)
                     {
                         m_vMineTabel[i+1][j+1]=9;
                     }
                     else
                     {
                         m_vMineTabel[i+1][j+1]/=10;
                     }
                }
                //右击问号态的格子，转换为无状态
                else if(m_vMineTabel[i+1][j+1]==-10||m_vMineTabel[i+1][j+1]>=9)//判断是否标？
                {
                    m_vMap[i][j]->setIcon(QIcon(":/prefix1/image/blank.png"));
                    if(m_vMineTabel[i+1][j+1]==9)
                            m_vMineTabel[i+1][j+1]=0;
                    else
                    {
                        m_vMineTabel[i+1][j+1]/=10;
                    }
                }
            });
        }
    }

}
//实现0号区域的递归
void GameWindow::mineDfs(int i, int j, int count)
{
    if(i<0 || j<0 || i>=m_nHeight || j>=m_nWidth || m_vMineTabel[i+1][j+1] == -2 || count == 0 || (m_vMineTabel[i+1][j+1] >= 99) || (m_vMineTabel[i+1][j+1] >= 9))
        return;//递归结束
    if(m_vMineTabel[i+1][j+1] != 0)
    {
        QString temp = QString::number(m_vMineTabel[i+1][j+1]);//将int转换为QString
        m_vMap[i][j]->setText(temp); //按钮显示周围雷数
        --m_nWinCount;
        m_vMap[i][j]->setStyleSheet("background-image: url(:/prefix1/image/blank.png);");//设置按钮背景图片
        m_vMineTabel[i+1][j+1] = -2;
    }//递归结束
    else
    {//对于0号格子
        --count;
        //m_vMap[i][j]->setText("0");
        --m_nWinCount;
        m_vMap[i][j]->setStyleSheet("background-image: url(:/prefix1/image/blank.png);");//注意地址的写法!!!!!!!
        m_vMineTabel[i+1][j+1] = -2;
        for (int x = i - 1; x < i + 2; x++)
        {
            for (int y = j - 1; y < j + 2; y++)
            {
                //if (!(i == x && j == y))
                if(x!=y||y!=j)
                {
                    mineDfs(x,y,count);
                }
            }
        }

    }
}

int GameWindow::gameLevel()
{
    if(m_nHeight==30&&m_nWidth==16&&m_nMineNumber==99)
    {
        Game_Level=2;
    }

    else if(m_nHeight==16&&m_nWidth==16&&m_nMineNumber==40)
    {
        Game_Level=1;
    }

    else if(m_nHeight==10&&m_nWidth==10&&m_nMineNumber==10)
    {
        Game_Level=0;
    }

    else
    {
        Game_Level=-1;
    }


    return Game_Level;
}



void GameWindow::gameOver(bool isWin)
{
    if(isWin)
    {
        if(this->m_nWinCount==0)//如果所有非雷区均被点击,游戏胜利
        {
            timer->disconnect();
            this->mapLight();
            ui->Button_certral->setIcon(QIcon(":/prefix1/image/qinqin.png"));
            QString q="恭喜你 "+user_name+" 用时 ";
            QString a=QString::number(sec)+"s";
            QString b=q+a;

            QSqlQuery query;
            query.prepare("insert into records(user_name,game_level,game_time)"
                          "values(:user_name,:game_level,:game_time)");
            query.bindValue(":user_name",user_name);
            query.bindValue(":game_level",gameLevel());
            query.bindValue(":game_time",sec);
            query.exec();


            QMessageBox::information(this,"提示",/*"恭喜你"*/b,QMessageBox::Ok);
            emit setIsInit();
        }
    }
    else//游戏失败
    {
        this->mapLight();
        timer->disconnect();
        ui->Button_certral->setIcon(QIcon(":/prefix1/image/kuku.png"));
        QString q="可惜呀 "+user_name+" 用时 ";
        QString a=QString::number(sec)+"s";
        QString b=q+a+" 难度："+QString::number(gameLevel());

//        QSqlQuery query;
//        query.prepare("insert into records(user_name,game_level,game_time)"
//                      "values(:user_name,:game_level,:game_time)");
//        query.bindValue(":user_name",user_name);
//        query.bindValue(":game_level",gameLevel());
//        query.bindValue(":game_time",sec);

        QMessageBox::information(this,"提示",b,QMessageBox::Ok);
        emit setIsInit();
    }
}

void GameWindow::mapLight()
{
    for(int i=0;i<m_nHeight;i++)
    {
        for(int j=0;j<m_nWidth;j++)
        {
            m_vMap[i][j]->disconnect();//无法再点击
            if(m_vMineTabel[i+1][j+1]==-1)
            {
                m_vMap[i][j]->setIcon(QIcon(":/prefix1/image/mine.png"));
            }
            else if(m_vMineTabel[i+1][j+1]>90)
            {
                m_vMap[i][j]->setIcon(QIcon(":/prefix1/image/err.png"));
            }
        }
    }
}

//提供给外部函数用于修改成员的函数
void GameWindow::setHeight(int h)
{
    m_nHeight=h;
}
void GameWindow::setWidth(int w)
{
    m_nWidth=w;
}
void GameWindow::setMineNumber(int m)
{
    m_nMineNumber=m;
}
