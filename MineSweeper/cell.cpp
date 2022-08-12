#include "cell.h"
#include "config.h"

Cell::Cell(QWidget *parent) : QPushButton(parent)
{
    init();    
    skinType = 1;
}

void Cell::init(){
    opened = false;
    mine = false;
    flag = false;
    neighborMines = 0;
    updateImg();
}

void Cell::updateImg(){ //更新图片
    if(opened){ //已经打开
            if(mine){ //如果有雷
                setStyleSheet(QString(MINE_IMG).arg(skinType));
            }else{ //如果没有雷，即空或数字
                setStyleSheet(QString(NUMBER_IMG).arg(skinType).arg(neighborMines));
            }
        }else{ //未被打开
            if(flag){ //如果被标记
                setStyleSheet(QString(FLAG_IMG).arg(skinType));
            }else{ //如果未被标记，即常态
                setStyleSheet(QString(INITIAL_IMG).arg(skinType));
            }
        }
}

void Cell::leftClick(){
    if(!opened && !flag){ //如果没有被标记并且未被打开
        setOpened(true); //将这个格子设置为已打开
        emit firstClickSignal(row, col);
        updateImg(); //更新图标
        if(!mine && neighborMines == 0){ //如果不是地雷且为空，则发送信号
            emit openOnNone(row, col);
        }
    }
}

void Cell::rightClick(){
    if(!opened){ //如果右击时格子没有被打开，则标记为旗帜
        setFlag(!flag);
        updateImg();
    }
}

void Cell::doubleClick(){
    if((opened && neighborMines != 0)||(!opened && flag)){ //已经打开了，并且是有数字的，或者是没有被打开但是有旗帜标记的
        emit doubleClickSignal(row, col);
    }
}

void Cell::mousePressEvent(QMouseEvent *event){

    if(event->buttons() == (Qt::LeftButton | Qt::RightButton)){ //双击
        doubleClick();
    }else if(event->button() == Qt::LeftButton){ //左击
        leftClick();
    }else if(event->button() == Qt::RightButton){ //右击
        rightClick();
    }

    emit updateConditionSignal();
}

