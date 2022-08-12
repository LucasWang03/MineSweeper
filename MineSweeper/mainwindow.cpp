#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));

    //初始化
    init();
}

void MainWindow::init(){
    //读取数据
    dataManager.load();

    //初始用户名为null
    username = "null";

    //获取游戏场景类
    scenes = ui->scenes;
    gameScene = (GameScene *)scenes->widget(GAME);

    //获取并设置各种子控件
    userEidt = ui->userWidget->findChild<QLineEdit*>("userEdit");
    ui->rowSpin->setMaximum(MAX_ROW);
    ui->rowSpin->setMinimum(2);
    ui->colSpin->setMaximum(MAX_COL);
    ui->colSpin->setMinimum(2);
    ui->minesSpin->setMaximum(MAX_MINES);

    //设置为初始页面
    scenes->setCurrentIndex(MAIN);
    //连接游戏场景和主场景
    connect(gameScene, &GameScene::gameOverSignal, this, &MainWindow::gameOver);

    //隐藏关于界面
    ui->aboutWidget->hide();
    //隐藏用户名输入界面
    ui->userWidget->hide();
    //隐藏自定义界面
    ui->settingWidget->hide();

    //排行榜设置信息并添入QLabel
    ui->rankInfo1->setText("排名\t玩家\t\t时长");
    ui->rankInfo2->setText("排名\t玩家\t\t时长");
    ui->rankInfo3->setText("排名\t玩家\t\t时长");
    for(int i = 0; i < MAX_RANK; ++i){
        ui->easyRanking->addItem(&rankingLabels[0][i]);
        ui->mediumRanking->addItem(&rankingLabels[1][i]);
        ui->hardRanking->addItem(&rankingLabels[2][i]);
    }

    //显示排行榜
    displayRanking(EASY);
    displayRanking(MEDIUM);
    displayRanking(HARD);
}

void MainWindow::setAllSkinType(int s){
    gameScene->setAllSkinType(s);
}

void MainWindow::gameOver(bool isVictory, MODE difficulty)
{
    scenes->setCurrentIndex(GAME_OVER);

    //表情设置
    if(isVictory){
        ui->faceLabel->setStyleSheet("image: url(:/res/win.png);");
    }else{
        ui->faceLabel->setStyleSheet("image: url(:/res/lose.png);");
    }

    //游戏时间
    ui->timeLabel->setText(QString::number(gameScene->gameTime) + "s");

    //显示难度
    if(difficulty == EASY){
        ui->modeLabel->setText("简单级");
    }else if(difficulty == MEDIUM){
        ui->modeLabel->setText("普通级");
    }else if(difficulty == HARD){
        ui->modeLabel->setText("困难级");
    }else{
        ui->modeLabel->setText("自定义");
    }

    //产生新的游戏纪录
    GameRecord newRecord{username, gameScene->gameTime, difficulty};

    //新记录是否上排行榜
    if(isVictory && updateRanking(newRecord)){
        ui->newRecordLabel->show();
    }else{
        ui->newRecordLabel->hide();
    }
}

bool MainWindow::updateRanking(GameRecord newRecord){
    //获取游戏难度
    int mode = newRecord.difficulty;

    //自定义模式不会更新游戏记录
    if(mode == OTHER)
        return false;

    //如果数据更新成功，则更新排行榜
    if(dataManager.updateData(newRecord)){
        //显示排行榜列表
        displayRanking(mode);
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::displayRanking(int mode){
    for(int i = 0; i < dataManager.ranking[mode].size(); ++i){
        GameRecord record = dataManager.ranking[mode][i];
        rankingLabels[mode][i].setText(QString::number(i+1)+"              "+
                                       record.username+"\t         "+QString::number(record.gameTime));
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_gameBtn_clicked()
{
    scenes->setCurrentIndex(SETTING);
}


void MainWindow::on_rankBtn_clicked()
{
    scenes->setCurrentIndex(RANKING);
}


void MainWindow::on_skinBtn_clicked()
{
    scenes->setCurrentIndex(THEME_SKIN);
}


void MainWindow::on_exitBtn_clicked()
{
    //保存数据
    dataManager.save();
    this->close();
}


void MainWindow::on_userBtn_clicked()
{
    ui->userWidget->show();
}


void MainWindow::on_yesBtn_clicked()
{
    username = userEidt->text();
    if(username == "")
        username = "null";
    userEidt->setText("");
    ui->userWidget->hide();
}


void MainWindow::on_noBtn_clicked()
{
    userEidt->setText("");
    ui->userWidget->hide();
}


void MainWindow::on_helpBtn_clicked()
{
    ui->aboutWidget->show();
}


void MainWindow::on_returnBtn_clicked()
{
    scenes->setCurrentIndex(MAIN);
}


void MainWindow::on_returnBtn_2_clicked()
{
    scenes->setCurrentIndex(MAIN);
}


void MainWindow::on_returnBtn_3_clicked()
{
    scenes->setCurrentIndex(MAIN);
}


void MainWindow::on_easyBtn_clicked()
{
    gameScene->setMap(EASY_ROW, EASY_COL, EASY_MINES);
    gameScene->start();
    scenes->setCurrentIndex(GAME);
}


void MainWindow::on_mediumBtn_clicked()
{
    gameScene->setMap(MEDIUM_ROW, MEDIUM_COL, MEDIUM_MINES);
    gameScene->start();
    scenes->setCurrentIndex(GAME);
}


void MainWindow::on_hardBtn_clicked()
{
    gameScene->setMap(HARD_ROW, HARD_COL, HARD_MINES);
    gameScene->start();
    scenes->setCurrentIndex(GAME);
}


void MainWindow::on_setBtn_clicked()
{
    ui->settingWidget->show();
}


void MainWindow::on_yesBtn_2_clicked()
{
    gameScene->setMap(ui->rowSpin->value(), ui->colSpin->value(), ui->minesSpin->value());
    gameScene->start();
    ui->settingWidget->hide();
    scenes->setCurrentIndex(GAME);
}


void MainWindow::on_noBtn_2_clicked()
{
    ui->settingWidget->hide();
}


void MainWindow::on_homeBtn_clicked()
{
    scenes->setCurrentIndex(MAIN);
}


void MainWindow::on_restartBtn_clicked()
{
    gameScene->start();
}

void MainWindow::on_OKBtn_clicked()
{
    ui->aboutWidget->hide();
}


void MainWindow::on_skin1Btn_clicked()
{
    setAllSkinType(1);
    ui->skinName->setText("默认");
    ui->skinPreview->setStyleSheet(QString(SKIN_PREVIEW).arg(1));
    ui->skinDescrip->setText(SKIN_DESCRIPTION1);

}


void MainWindow::on_skin2Btn_clicked()
{
    setAllSkinType(2);
    ui->skinName->setText("灰金");
    ui->skinPreview->setStyleSheet(QString(SKIN_PREVIEW).arg(2));
    ui->skinDescrip->setText(SKIN_DESCRIPTION2);
}


void MainWindow::on_skin3Btn_clicked()
{
    setAllSkinType(3);
    ui->skinName->setText("晴空");
    ui->skinPreview->setStyleSheet(QString(SKIN_PREVIEW).arg(3));
    ui->skinDescrip->setText(SKIN_DESCRIPTION3);
}


void MainWindow::on_homeBtn_2_clicked()
{
    scenes->setCurrentIndex(MAIN);
}


void MainWindow::on_restartBtn_2_clicked()
{
    gameScene->start();
    scenes->setCurrentIndex(GAME);
}


void MainWindow::on_returnBtn_4_clicked()
{
    scenes->setCurrentIndex(GAME);
}

