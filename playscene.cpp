#include "playscene.h"
#include <QPainter>
#include <QPixmap>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "mypushbutton.h"
#include <QLabel>
#include <QFont>
#include "dataconfig.h"
#include "mycoin.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QSoundEffect>
PlayScene::PlayScene(QWidget *parent)
    : QMainWindow{parent}
{}

PlayScene::PlayScene(int index)
{
    QSoundEffect * sound1 = new QSoundEffect(this);
    sound1->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    QSoundEffect * sound2 = new QSoundEffect(this);
    sound2->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    QSoundEffect * sound3 = new QSoundEffect(this);
    sound3->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));

    //赋值给成员变量
    this->levelIndex = index;

    //PlayScene场景基本设置
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(QPixmap(":/res/Coin0001.png")));
    this->setWindowTitle("翻金币中");
    QMenuBar * menuBar = this->menuBar();
    this->setMenuBar(menuBar);
    QMenu * menu = menuBar->addMenu("开始");
    QAction * quitAction = this->addAction("退出");
    menu->addAction(quitAction);
    //点击退出Action，关闭窗口
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });

    //显示当前关卡号Label,设置字体，设置setGeometry位置
    QLabel * showIndex = new QLabel(this);
    showIndex->setText(QString("Level:%1").arg(QString::number(this->levelIndex)));
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    showIndex->setFont(font);
    showIndex->setGeometry(QRect(30,this->height() - 50,120,50));//设置大小和位置


    //返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
    //点击返回按钮，触发信号
    connect(closeBtn,&MyPushButton::clicked,this,[=](){
        //因为playscene一返回就删除内存，所以声音很短,所以就要在chooseLevelScene中添加音效
        //sound2->play();
        QTimer::singleShot(100,this,[=](){
        this->hide();
        emit this->chooseSceneBack();
         });
    });

    //创建金币背景图

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //硬币绘制背景图片
            QLabel * label = new QLabel(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move(59 + i*50,204+j*50);
        }
    }

    //设置胜利图标,写在外面，不要写在for循环里面
    QLabel * lbl = new QLabel(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    lbl->setGeometry(0,0,pix.width(),pix.height());
    lbl->setPixmap(pix);
    lbl->move(this->width()*0.5 - pix.width()*0.5,-pix.height());

    dataConfig gameConfig;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = gameConfig.mData[this->levelIndex][i][j];
            QString img;
            if(this->gameArray[i][j] == 1)
            {
                img = ":/res/Coin0001.png";
            }
            else
            {
                img = ":/res/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(img);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->frontOrBack = this->gameArray[i][j];
            this->coinBtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,this,[=](){
                sound1->play();
                coin->changeFace();
                //数组内部标识同步改变
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                QTimer::singleShot(100,this,[=](){
                    if(coin->posX+1 <= 3)
                    {
                        coinBtn[coin->posX + 1][coin->posY]->changeFace();
                        gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY] == 0?1:0;
                    }
                    if(coin->posX-1 >= 0)
                    {
                        coinBtn[coin->posX - 1][coin->posY]->changeFace();
                        gameArray[coin->posX-1][coin->posY] =  gameArray[coin->posX-1][coin->posY] == 0 ? 1:0;
                    }
                    if(coin->posY-1 >= 0)
                    {
                        coinBtn[coin->posX ][coin->posY-1]->changeFace();
                        gameArray[coin->posX][coin->posY-1] =  gameArray[coin->posX][coin->posY-1] == 0 ? 1:0;
                    }
                    if(coin->posY+1 <= 3)
                    {
                        coinBtn[coin->posX ][coin->posY+1]->changeFace();
                        gameArray[coin->posX][coin->posY+1] =  gameArray[coin->posX][coin->posY+1] == 0 ? 1:0;
                    }

                    //写在singleshot里面
                    this->isWin =true;
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j =0; j < 4; j++)
                        {
                            if(gameArray[i][j] == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                   this->coinBtn[i][j]->isWin = this->isWin;

                    //写在singleshot里面
                    if(this->isWin)
                    {
                       sound3->play();
                       for(int i = 0; i < 4; i++)
                        {
                            for(int j =0; j < 4; j++)
                            {
                                //你可上我探索的好久啊啊啊啊啊啊，这个位置
                                this->coinBtn[i][j]->isWin = this->isWin;
                            }
                        }

                        QPropertyAnimation* animation = new QPropertyAnimation(lbl,"geometry");
                        animation->setDuration(1000);
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->setStartValue(QRect(lbl->x(),lbl->y(),lbl->width(),lbl->height()));
                        animation->setEndValue(QRect(lbl->x(),lbl->y()+114,lbl->width(),lbl->height()));
                        animation->start();
                    }
                });



            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}

// void PlayScene::mousePressEvent(QMouseEvent *event)
// {
//     if(this->isWin)
//     {
//         return;
//     }
//     else
//     {
//         return QMainWindow::mousePressEvent(event);
//     }
// }
