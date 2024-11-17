#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QMenuBar>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include<QSoundEffect>
#include<QUrl>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    QSoundEffect * sound = new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    QSoundEffect * sound2 = new QSoundEffect(this);
    sound2->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));


    //选择关卡的边缘样式设置
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(QPixmap(":/res/Coin0001.png")));
    this->setWindowTitle("请选择一个关卡");

    //创建菜单栏
    QMenuBar * menuBar = this->menuBar();
    this->setMenuBar(menuBar);
    QMenu * menu = menuBar->addMenu("开始");
    QAction * quitAction = addAction("退出");
    menu->addAction(quitAction);

    //点击开始菜单的退出Action，触发关闭槽函数
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
        QTimer::singleShot(500,this,[=](){

        });
    });

    //创建返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
    //点击返回按钮,隐藏当前关卡，触发信号
    connect(closeBtn,&MyPushButton::clicked,this,[=](){
        QTimer::singleShot(10,this,[=](){
            sound2->play();
            this->hide();
            //自定义信号
            emit this->chooseSceneBack();
        });
    });

    //创建关卡按钮
    for(int i = 0; i < 20; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(20 + (i%4) * 70, 130 + (i/4) * 70);
        //在按钮上显示文字
        QLabel * label = new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//设置标签上的数字对中
        label->move(20 + (i%4) * 70, 130 + (i/4) * 70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);//鼠标事件穿透

        //点击关卡按钮进入PlayScene
        connect(menuBtn,&MyPushButton::clicked,this,[=](){
            sound->play();
            if(this->pScene == nullptr)
            {

                this->hide();
                this->pScene = new PlayScene(i+1);
                pScene->setGeometry(this->geometry());
                this->pScene->show();
                //监听来自PlayScene的信号，并销毁pScene
                connect(pScene,&PlayScene::chooseSceneBack,this,[=](){
                    sound2->play();
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = nullptr;
                });
            }
        });
    }





}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()*0.5 - pix.width()*0.5 , 30 , pix.width(),pix.height(),pix);

}
