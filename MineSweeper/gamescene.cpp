#include "gamescene.h"

GameScene::GameScene(QWidget *parent)
    : QWidget{parent}
{
    mines = EASY_MINES;
    rows = EASY_ROW;
    cols = EASY_COL;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&](){gameTime += 0.1;
        //更新游戏时间
        gameTimeLabel->setText(QString::number(gameTime));});

    //计时器图标
    timerLabel = new QLabel(this);
    timerLabel->resize(40, 40);
    timerLabel->move(370, 10);
    timerLabel->setStyleSheet("image: url(:/res/timer.png);");

    //显示游戏时间
    gameTimeLabel = new QLabel(this);
    gameTimeLabel->resize(100, 40);
    gameTimeLabel->move(430, 10);
    gameTimeLabel->setStyleSheet("color: rgb(97, 97, 97);");
    gameTimeLabel->setText("0.0");

    //旗子图标
    flagLabel = new QLabel(this);
    flagLabel->resize(40, 40);
    flagLabel->move(540, 10);
    flagLabel->setStyleSheet("image: url(:/res/flag.png);");

    //显示剩余旗子
    restFlagLabel = new QLabel(this);
    restFlagLabel->resize(40, 40);
    restFlagLabel->move(590, 10);
    restFlagLabel->setStyleSheet(" color: rgb(97, 97, 97);");

    init();
}

void GameScene::init(){
    qsrand((unsigned)time(nullptr)); //设置随机数种子

    for(int i = 0; i < MAX_ROW;++i){
        for(int j = 0; j < MAX_COL;++j){
            //初始化cell数组
            cells[i][j] = new Cell(this);
            cells[i][j]->setRowAndCol(i, j);
            cells[i][j]->resize(SIZE, SIZE);

            //连接各个cell和游戏主界面
            connect(cells[i][j], &Cell::firstClickSignal, this, &GameScene::createMines);
            connect(cells[i][j], &Cell::updateConditionSignal, this, &GameScene::updateCondition);
            connect(cells[i][j], &Cell::openOnNone, this, &GameScene::findNoMines);
            connect(cells[i][j], &Cell::doubleClickSignal, this, &GameScene::doubleClick);
        }
    }

}


void GameScene::setMap(int r,int c,int m){ //设置地图大小和地雷数
    rows = r;
    cols = c;
    mines = m;

    //确保地雷数不会过多
    if(m >= r * c){
        mines = r * c - 1;
    }

    if(r == EASY_ROW && c == EASY_COL && m == EASY_MINES){
        difficulty = EASY;
    }else if(r == MEDIUM_ROW && c == MEDIUM_COL && m == MEDIUM_MINES){
        difficulty = MEDIUM;
    }else if(r == HARD_ROW && c == HARD_COL && m == HARD_MINES){
        difficulty = HARD;
    }else{
        difficulty = OTHER;
    }
}

void GameScene::start(){
    //清除上一次游戏的cells
    QList<Cell*> lastCells = this->findChildren<Cell*>();
    for(int i = 0; i < lastCells.size();++i){
        lastCells.at(i)->init(); //将cell重新初始化
        lastCells.at(i)->hide(); //将cell从游戏场景中移除
    }

    //重新分配cells并设置位置
    for(int i = 0; i < rows;++i){
        for(int j = 0; j < cols;++j){
            cells[i][j]->show();
            cells[i][j]->move((GAME_WIDTH - (SIZE + GAP) * cols) / 2 + (SIZE + GAP) * i, 70 + (SIZE + GAP) * j);
        }
    }

    //重新设置第一次点击
    isFirstClick = true;

    //重新设置为游戏未结束
    isGameOver = false;

    //设置剩余旗子数
    restFlags = mines;
    restFlagLabel->setText(QString::number(restFlags));

    //重置游戏时间
    gameTime = 0; 
    timer->stop();
    gameTimeLabel->setText("0.0");
}

void GameScene::updateCondition(){
    //如果游戏已结束，则不再更新状态
    if(isGameOver){
        return;
    }

    int blocks = 0; //被打开且没有地雷的cell数
    int restMines = 0; //有地雷但未被标记的cell数
    int flags = 0; //被标记的cell数

    for(int i = 0; i < rows;++i){
        for(int j = 0; j < cols;++j){

            //被打开且没有地雷的cell
            if(cells[i][j]->isOpened() && !cells[i][j]->isMine())
                blocks++;

            //被标记的cell
            if(cells[i][j]->isFlag())
                flags++;

            //有地雷但未被标记的cell
            if(cells[i][j]->isMine() && !cells[i][j]->isFlag())
                restMines++;

            //如果打开了地雷，则游戏失败
            if(cells[i][j]->isOpened() && cells[i][j]->isMine()){
                emit gameOverSignal(false, difficulty);
                isGameOver = true;
                timer->stop();
                return;
            }
        }
    }

    //如果所有没有地雷的cell都被打开，则游戏胜利
    if(blocks == rows * cols - mines){
        emit gameOverSignal(true, difficulty);
        isGameOver = true;
        timer->stop();
        return;
    }

    //更新剩余旗子数
    restFlags = mines - flags;
    restFlagLabel->setText(QString::number(restFlags));
}

void GameScene::createMines(int row, int col){ 
    if(!isFirstClick)
        return;
    isFirstClick = false;

    //已埋地雷数
    int minesCnt = 0;

    //产生地雷
    while(minesCnt < mines){
        int i = qrand() % rows;
        int j = qrand() % cols;

        //避免重复布置地雷，同时第一次点击的cell不能是地雷
        if(!cells[i][j]->isMine() && (i != row || j != col)){
            cells[i][j]->setMine(true);
            minesCnt++;
        }
    }

    int nx, ny, neighborMines;
    //设置周围砖块数
    for(int i = 0; i < rows;++i){
        for(int j = 0; j < cols;++j){
            neighborMines = 0;
            for(int k = 0; k < 8; ++k){ //遍历它周围的八个格子
                nx = i + dx[k];
                ny = j + dy[k];
            if(0 <= nx && nx < rows && 0 <= ny && ny < cols){ //判断是否超出边界
                if(cells[nx][ny]->isMine()){ //这八个格子中如果有雷
                    neighborMines++;
                    }
                }
            }
            cells[i][j]->setNeighborMines(neighborMines); //设置周围地雷数
        }
    }

    //开始计时
    timer->start(100);
}

void GameScene::findNoMines(int row, int col){
    //把cell打开
    cells[row][col]->setOpened(true);
    cells[row][col]->updateImg();

    //遇到有数字的cell就停止搜索
    if(cells[row][col]->getNeighborMines() != 0)
        return;

    int nx, ny;
    //遍历周围的cell
    for(int i = 0; i < 8;++i){
        nx = row + dx[i];
        ny = col + dy[i];

        //若未超出边界且为被打开，则继续搜索
        if(0 <= nx && nx < rows && 0 <= ny && ny < cols && !cells[nx][ny]->isOpened()){
            findNoMines(nx, ny);
        }
    }
}

void GameScene::doubleClick(int row, int col){
    int nx, ny;
    int neighborFlags = 0;

    //遍历周围的cell，计算周围的flag数量
    for(int i = 0; i < 8;++i){
        nx = row + dx[i];
        ny = col + dy[i];
        //超出边界则不计入
        if(nx < 0 || nx >= rows || ny < 0 || ny >= cols)
            continue;
        //未被打开且被flag标记
        if(!cells[nx][ny]->isOpened() && cells[nx][ny]->isFlag())
            neighborFlags++;
    }

    //若周围的地雷数与flag数不相等，则不能触发双击功能
    if(cells[row][col]->getNeighborMines() != neighborFlags)
        return;

    //触发双击功能
    for(int i = 0; i < 8;++i){
        nx = row + dx[i];
        ny = col + dy[i];
        //超出边界则不进行操作
        if(nx < 0 || nx >= rows || ny < 0 || ny >= cols)
            continue;

        //打开周围未被打开和标记的cell
        if(!cells[nx][ny]->isOpened() && !cells[nx][ny]->isFlag()){
            cells[nx][ny]->leftClick();
        }
    }
}

void GameScene::setAllSkinType(int s){
    for(int i = 0; i < MAX_ROW;++i){
        for(int j = 0; j < MAX_COL;++j){
            cells[i][j]->setSkinType(s);
        }
    }
}
