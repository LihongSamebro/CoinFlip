#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include "mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);

    void paintEvent(QPaintEvent *event);

    //成员变量，记录关卡索引
    int levelIndex;

    //记录当前关卡数组
    int gameArray[4][4];

    MyCoin * coinBtn[4][4];
    bool isWin = true;

    //void mousePressEvent(QMouseEvent *event);




signals:
    void chooseSceneBack();
    //pass void isWinSignal();
};

#endif // PLAYSCENE_H
