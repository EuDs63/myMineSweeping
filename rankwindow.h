#ifndef RANKWINDOW_H
#define RANKWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include<QSqlQuery>

namespace Ui {
class RankWindow;
}

class RankWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RankWindow(QString name,QWidget *parent = nullptr);
    ~RankWindow();

    //void showMyLow();




private slots:
    //void on_ShowInfotableView_changed();
    void showMyLow();
    void showMyMiddle();
    void showMyHigh();
    void showGlobalLow();
    void showGlobalMiddle();
    void showGlobalHigh();

private:
    Ui::RankWindow *ui;
    QString user_name;//用户名
    QStandardItemModel *recordsModel;
    int m_iCurTable; //表示当前表格显示的信息，0--初始状态；1--显示我的初级；2--显示我的中级；3--显示我的高级；
                     //4--显示总记录初级;5--显示总记录中级；5--显示总记录高级
};

#endif // RANKWINDOW_H
