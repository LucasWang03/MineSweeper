#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

//配置文件

//游戏主窗口配置
#define GAME_TITLE "Mine Sweeper"
#define GAME_ICON ":/res/bomb.png"
#define GAME_WIDTH 1000
#define GAME_HEIGHT 600

//cell类配置
#define SIZE 30
#define GAP 3
#define MAX_ROW 15
#define MAX_COL 20
#define MAX_MINES 60
#define INITIAL_IMG "border-image: url(:/res/skin%1/initial.png);"
#define FLAG_IMG "border-image: url(:/res/skin%1/flag.png);"
#define NUMBER_IMG "border-image: url(:/res/skin%1/%2.png);"
#define MINE_IMG "border-image: url(:/res/skin%1/mine.png);"

//难度设置配置
#define EASY_ROW 8
#define EASY_COL 8
#define EASY_MINES 8
#define MEDIUM_ROW 12
#define MEDIUM_COL 12
#define MEDIUM_MINES 20
#define HARD_ROW 15
#define HARD_COL 15
#define HARD_MINES 35

#define MAX_RANK 15

//皮肤配置
#define SKIN_PREVIEW "image: url(:/res/skin%1/preview.png);\
                background-color: rgba(97, 97, 97, 0.1);\
                border:2px groove gray;\
                border-radius:10px;\
                padding:2px 4px;"
#define SKIN_DESCRIPTION1 "经典的默认皮肤，极具简洁而又不失精致。\n无需充值就能获得！！！"
#define SKIN_DESCRIPTION2 "极具质感的磨砂纹理，透露出些许高贵和优雅的灰金色。\n或许和默认皮肤没多大差别？"
#define SKIN_DESCRIPTION3 "风走过的操场，太阳带来一丝暖意，蝉鸣悠悠唱起。\n七月又静悄悄地过去了……"

//游戏场景枚举
enum SCENE_TYPE{MAIN, SETTING, GAME, RANKING, THEME_SKIN, GAME_OVER};

//难度枚举
enum MODE{EASY = 0, MEDIUM = 1, HARD = 2, OTHER = 3};

//每一次的游戏记录
struct GameRecord{
    QString username; //用户名
    qreal gameTime; //游戏时长
    qint64 difficulty; //难度

    // 操作运算符重载
    bool operator==(const GameRecord& other){
        return( username == other.username) && (gameTime == other.gameTime);
    }

    bool operator<(const GameRecord& other){
        if(gameTime < other.gameTime)
            return true;
        else if(gameTime > other.gameTime)
            return false;
        else
            return username < other.username;
    }

    bool operator>(const GameRecord& other){
        if(gameTime > other.gameTime)
            return true;
        else if(gameTime < other.gameTime)
            return false;
        else
            return username > other.username;
    }
};

#endif // CONFIG_H
