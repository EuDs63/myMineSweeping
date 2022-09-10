#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QMouseEvent>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void rightChecked();
    void leftChecked();
    void leftRightPressed();
    void leftRightReleased();
    void leftReleased();

private:
    bool m_bLeftMousePressed=false;
    bool m_bRightMousePressed=false;

};

#endif // MYPUSHBUTTON_H
