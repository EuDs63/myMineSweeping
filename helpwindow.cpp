#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
     ui->helpText->setStyleSheet("background:transparent;border-width:0;border-style:outset");
     setWindowTitle("扫雷帮助");
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
