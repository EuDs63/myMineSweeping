#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include"GameWindow.h"
#include <QMainWindow>
#include<QMessageBox>

namespace Ui {
class ChoiceWindow;
}
class GameWindow;

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChoiceWindow(GameWindow *parent = nullptr);
    ~ChoiceWindow();
    void saveDefault(GameWindow * parent);//储存玩家选择的默认的难度
    bool saveCustom(GameWindow * parent);//储存玩家自定义的参数并初始化，设置参数成功返回true

private:
    Ui::ChoiceWindow *ui;
};

#endif // CHOICEWINDOW_H
