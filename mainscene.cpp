#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QTimer>
#include <QSoundEffect>
#include<QUrl>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置音乐
    QSoundEffect * sound1 = new QSoundEffect(this);
    sound1->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //设置主窗口边缘样式
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(QPixmap(":/res/Coin0001.png")));
    this->setWindowTitle("老帮主帮你翻金币");

    //设置开始菜单退出Action
    connect(ui->actionQuit,&QAction::triggered,this,&MainScene::close);

    //设置开始按钮，为自定义的MyPushButton
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width()*0.5 - startBtn->width()*0.5),this->height()*0.7);
    //实例化选关关卡
    ChooseLevelScene * chooseScene = new ChooseLevelScene(this);
    //设置开始按钮点击特效
    connect(startBtn,&MyPushButton::clicked,this,[=](){

        sound1->play();

        startBtn->zoomDown();
        startBtn->zoomUp();
    //点击按钮，按钮特效结束后，隔0.5秒进入ChooseLevelScene关卡
        QTimer::singleShot(10,this,[=](){
            //设置打开chooselevelscene的位置
            chooseScene->setGeometry(this->geometry());
            this->hide();
            chooseScene->show();
        });
    });

    //一直监听从ChooseLevelScene发来的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry());
        this->show();
    });




}


void MainScene::paintEvent(QPaintEvent *event)
{
    //设置主窗口背景和标题
    QPixmap pix;
    QPainter painter(this);
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()* 0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}
