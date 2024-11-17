#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include "playscene.h"
#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    //创建不同对象的PlayScene
    PlayScene * pScene = nullptr;

signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
