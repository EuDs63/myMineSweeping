#include "mypushbutton.h"

myPushButton::myPushButton(QWidget *parent) : QPushButton(parent)
{

}

void myPushButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        emit rightChecked();
        m_bLeftMousePressed=true;

    }//检测到右击则释放右击信号
    if(event->button()==Qt::LeftButton)
    {
        emit leftChecked();
        m_bRightMousePressed=true;

    }//检测到左击则释放左击信号

    if(m_bRightMousePressed==true&&m_bLeftMousePressed==true)
    {
        emit leftRightPressed();
    }

}

void myPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_bLeftMousePressed==true&&m_bRightMousePressed==true)
    {
        emit leftRightReleased();
    }
    else if(m_bRightMousePressed==true)
    {
        emit leftReleased();
    }
    m_bLeftMousePressed=false;
    m_bRightMousePressed=false;
}
