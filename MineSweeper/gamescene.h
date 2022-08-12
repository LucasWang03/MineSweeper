#ifndef GAMESCENE_H
#define GAMESCENE_H

//游戏场景类

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "config.h"
#include "cell.h"

class GameScene : public QWidget
{
    friend class MainWindow;
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);

    void init(); //游戏初始化
    void setMap(int r,int c,int m); //设置地图大小和地雷数
    void setAllSkinType(int s); //设置所有cell的皮肤类型
signals:
    void gameOverSignal(bool isVictory, MODE diff);

public slots:

    void start(); //游戏开始
    void createMines(int row, int col); //产生地雷
    void findNoMines(int row,int col); //dfs寻找无雷区
    void doubleClick(int row,int col); //某处双击
    void updateCondition(); //更新游戏界面状态

private:

    Cell *cells[MAX_ROW][MAX_COL];//figureMate类对象指针的二维数组。

    int mines; //地雷数
    int rows; //地图高度
    int cols; //地图
    bool isFirstClick; //是否是第一次点击
    bool isGameOver; //游戏是否已结束
    int restFlags;
    MODE difficulty; //游戏难度


    QTimer *timer; //计时器
    QLabel *timerLabel; //计时器图标
    QLabel *gameTimeLabel; //游戏时间标签
    double gameTime;
    QLabel *flagLabel; //旗子图标
    QLabel *restFlagLabel; //剩余旗子数

    //周围的八个点  坐标
    int dx[8]={-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8]={-1, 0, 1, -1, 1, -1, 0, 1};

};

#endif // GAMESCENE_H
