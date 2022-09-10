#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include"mypushbutton.h"
#include <QMainWindow>
#include<QVector>
#include<QPushButton>
#include<QMessageBox>
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QSqlQuery>

#include"logon.h"
#include"choicewindow.h"
#include"aboutwindow.h"
#include"helpwindow.h"
#include"rankwindow.h"

namespace Ui {
class GameWindow;
}

class logon;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QString name,QWidget *parent = nullptr);//构造函数
    ~GameWindow();//析构函数

    void initAll();//对全部进行初始化
    void initMineTable();//对雷表进行初始化
    int initTheRandom(int low,int high);//产生一个从low到high的随机数

    int aroundCount(int,int);//计算周围八格的雷数
    void mineDfs(int,int,int);//实现0的遍历
    void mapLight(); //点亮地图

    int gameLevel();//判断游戏难度
    void gameOver(bool);

    //提供给外部的接口，用于改变基本属性
    void setHeight(int);//高度
    void setWidth(int);//宽度
    void setMineNumber(int);//设置雷的数量


private:
    Ui::GameWindow *ui;
    int m_nWinCount;
    int m_nHeight=10;//默认每行十个按钮
    int m_nWidth=10;//默认每列十个按钮
    int m_nMineNumber=10;//实际的雷数
    int m_nMineCount;  //对雷的数目进行计数,是玩家认为的雷数
    QString user_name;//用户名
    int Game_Level;//游戏难度 -1自定义，0初级，1中级，2高级

    QVector<QVector<myPushButton*>> m_vMap;//按钮，操作的对象
    QVector<QVector<int>> m_vMineTabel;//用于存储雷的实际情况,值大于0时为周边的雷数，-1：有雷，-2：已被打开

    QTimer *timer;
    int sec=0;//后续得进一步修改

    bool m_bIsTimeCount=false;

signals:
    void setIsInit();
};

#endif // GAMEWINDOW_H
