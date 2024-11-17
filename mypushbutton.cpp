#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{

}
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    //设置成员变量
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressImg;

    //判断是否成功加载图片
    QPixmap pix;
    int ret = pix.load(this->normalImgPath);
    if(!ret)
    {
        qDebug() << "加载normalImg错误";
    }
    //设置MyPushButton的样式
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式
    this->setIcon(QIcon(pix));
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoomDown()
{
    QPropertyAnimation * downAnimation = new QPropertyAnimation(this,"geometry");
    downAnimation->setDuration(200);
    downAnimation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    downAnimation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线
    downAnimation->setEasingCurve(QEasingCurve::OutBounce);
    //播放完动画删除Animation
    downAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}
void MyPushButton::zoomUp()
{
    QPropertyAnimation * downAnimation = new QPropertyAnimation(this,"geometry");
    downAnimation->setDuration(200);
    downAnimation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    downAnimation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    downAnimation->setEasingCurve(QEasingCurve::OutBounce);
    //播放完动画删除Animation
    downAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

//设置按压鼠标时的图片
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressedImgPath);
        if(!ret)
        {
            qDebug() << "pressedImgPath出错";
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->normalImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug() << "normalImgPath出错";
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
