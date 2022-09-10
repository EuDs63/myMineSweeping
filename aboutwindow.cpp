#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    ui->aboutInfomation->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    setWindowTitle("关于扫雷");
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
