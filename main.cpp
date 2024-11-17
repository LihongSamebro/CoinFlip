#include "mainscene.h"
#include "dataconfig.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;

    // dataConfig data;
    // for(int i = 0; i < 4; i++)
    // {
    //     for(int j = 0; j < 4; j++)
    //     {
    //         qDebug() << data.mData[1][i][j];
    //     }
    // }

    w.show();
    return a.exec();
}
