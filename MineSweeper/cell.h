#ifndef CELL_H
#define CELL_H

/*
 * Cell类表示一个格子的各种信息
 */

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>

class Cell :public QPushButton
{
    Q_OBJECT
public:
    explicit Cell(QWidget *parent = nullptr);

    //getter和setter直接在头文件里实现
    void setRowAndCol(int r, int c){
        row = r;
        col = c;
    }
    void setOpened(bool o){ //模拟点击,打开
        opened =  o;
        updateImg();
    }
    void setMine(bool m){
        mine = m;
    }
    void setNeighborMines(int n){ //设置地雷个数
        neighborMines = n;
    }
    void setFlag(bool m){ //标记
        flag = m;
        updateImg();
    }
    bool isOpened(){ //判断是否打开过
        return opened;
    }
    bool isMine(){ //判断是不是雷
        return mine;
    }
    bool isFlag(){ //判断是否已被标记
        return flag;
    }
    int getNeighborMines(){ //得到雷数
        return neighborMines;
    }
    int getSkinType(){
        return skinType;
    }
    void setSkinType(int s){ //设置皮肤类型
        skinType = s;
    }

    void init();
    void leftClick(); //左键点击
    void rightClick(); //右键点击
    void doubleClick(); //双击
    void updateImg(); //更新显示

protected:
    void mousePressEvent(QMouseEvent *event)override;

signals:
    void firstClickSignal(int r, int c);
    void updateConditionSignal(); //更新游戏场景状态的信号
    void openOnNone(int r, int c); //自动打开空cell的功能信号
    void doubleClickSignal(int r, int c); //双击功能的信号

private:
    int row; //所在行数
    int col; //所在列数
    bool opened; //是否已经打开，默认设置为未打开
    bool mine; //是否有地雷，默认设置为没有
    bool flag; //是否被旗帜标记了，默认设置为没有被标记
    int neighborMines; //周围地雷个数
    int skinType; //皮肤类型
};

#endif // CELL_H
