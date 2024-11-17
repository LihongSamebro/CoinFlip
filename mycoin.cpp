#include "mycoin.h"
#include<QPixmap>
#include<QPainter>
#include<QDebug>
#include <QTimer>
#include<QMouseEvent>
#include <QLabel>
MyCoin::MyCoin(QWidget *parent)
    : QPushButton{parent}
{}
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        qDebug() << "btnImg路径出错" ;
    }

    //设置按钮基本样式
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{ border:0px; }");
    this->setIcon(QIcon(pix));
    this->setIconSize(QSize(pix.width(),pix.height()));


    //this->isWin = true;
    // for(int i = 0; i < 4; i++)
    // {
    //     for(int j = 0; j < 4; j++)
    //     {
    //         if(this->coinBtn[i][j]->frontOrBack == 0)
    //         {
    //             this->isWin = false;
    //             break;
    //         }
    //     }
    // }



}


void MyCoin::changeFace()
{
    this->isAnimation = true;

    //初始化QTImer,写在这里而不是构造函数中
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);



    if(this->frontOrBack)//如果是正面，执行下列代码
    {

        timer1->start(30);
        //设置翻转动画
        connect(timer1,&QTimer::timeout,this,[=](){
            QPixmap pix;
            pix.load(QString(":/res/Coin000%1.png").arg(this->min++));
            this->setFixedSize(pix.width(),pix.height());
            this->setStyleSheet("QPushButton{ border:0px; }");
            this->setIcon(QIcon(pix));
            this->setIconSize(QSize(pix.width(),pix.height()));
            if(this->min > this->max)
            {
                this->min = 1;
                timer1->stop();
                this->isAnimation = false;
            }
        });
        this->frontOrBack = false;
    }
    else
    {
        timer2->start(30);
        //设置翻转动画
        connect(timer2,&QTimer::timeout,this,[=](){
            QPixmap pix;
            pix.load(QString(":/res/Coin000%1.png").arg(this->max--));
            this->setFixedSize(pix.width(),pix.height());
            this->setStyleSheet("QPushButton{ border:0px; }");
            this->setIcon(QIcon(pix));
            this->setIconSize(QSize(pix.width(),pix.height()));
            if(this->max < this->min)
            {
                this->max = 8;
                timer2->stop();
                this->isAnimation = false;
            }
        });
        this->frontOrBack = true;
    }

}

void  MyCoin::mousePressEvent(QMouseEvent *e)
{


    if(this->isAnimation | this->isWin )
     {

        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}



