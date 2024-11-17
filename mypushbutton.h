#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数的重载，可以让 MyPushButton 提供正常显示的图片以及按下后显示的图片
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;
    QString pressedImgPath;

    //设置按钮的点击特效
    void zoomDown();
    void zoomUp();

    //重写鼠标事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
};

#endif // MYPUSHBUTTON_H
