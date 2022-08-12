#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QDebug>
#include "config.h"

class DataManager
{
public:
    DataManager();

    //三个难度的排行榜数据
    QVector<GameRecord> ranking[3];

    void load(); //读取数据
    void save(); //存数据
    bool updateData(GameRecord record); //更新数据
};

#endif // DATAMANAGER_H
