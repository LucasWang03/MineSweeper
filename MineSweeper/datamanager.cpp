#include "datamanager.h"

DataManager::DataManager()
{

}

void DataManager::load(){
    QFile file("rank.dat");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "打开文件失败";
        return;
    }

    QDataStream in(&file);
    GameRecord record;

    //读取文件
    while(!in.atEnd()){
        in >> record.username >> record.gameTime >> record.difficulty;
        ranking[record.difficulty].push_back(record);
    }

    file.close();
}

void DataManager::save(){
    QFile file("rank.dat");

    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "保存文件失败";
        return;
    }

    QDataStream out(&file);
    GameRecord record;

    //保存文件
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < ranking[i].size(); ++j){
            record = ranking[i][j];
            out << record.username;
            out << record.gameTime;
            out << record.difficulty;
        }
    }

    file.close();
}

bool DataManager::updateData(GameRecord record){
    //获得难度
    int mode = record.difficulty;

    //添加新记录
    ranking[mode].push_back(record);

    //进行排序
    std::sort(ranking[mode].begin(), ranking[mode].end());

    //去除多余记录，若新纪录排行第十五之后，返回false
    if(ranking[mode].size() > MAX_RANK){
        if(ranking[mode].back() == record){
            return false;
        }
        ranking[mode].pop_back();
    }

    return true;
}
