#ifndef MYCOIN_H
#define MYCOIN_H

#include<QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);

    int posX;
    int posY;
    bool frontOrBack;

    void changeFace();
    int min = 1; //最小图片
    int max = 8;
    QTimer * timer1; //正翻反面计时器
    QTimer * timer2;

    //是否在动画期间
    bool isAnimation  = false;
    void  mousePressEvent(QMouseEvent *e);

    //创建在这干嘛，有病是吧
    //MyCoin * coinBtn[4][4];

    //判断胜利
    bool isWin = false;

signals:
};

#endif // MYCOIN_H
