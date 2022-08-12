#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//主窗口类，管理各个场景类

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QStackedWidget>
#include <QListWidgetItem>

#include "cell.h"
#include "gamescene.h"
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gameOver(bool isVictory, MODE difficulty);

    void on_gameBtn_clicked();

    void on_rankBtn_clicked();

    void on_skinBtn_clicked();

    void on_exitBtn_clicked();

    void on_returnBtn_clicked();

    void on_returnBtn_2_clicked();

    void on_returnBtn_3_clicked();

    void on_easyBtn_clicked();

    void on_mediumBtn_clicked();

    void on_hardBtn_clicked();

    void on_homeBtn_clicked();

    void on_restartBtn_clicked();

    void on_OKBtn_clicked();

    void on_helpBtn_clicked();

    void on_skin1Btn_clicked();

    void on_skin2Btn_clicked();

    void on_skin3Btn_clicked();

    void on_yesBtn_clicked();

    void on_noBtn_clicked();

    void on_userBtn_clicked();

    void on_setBtn_clicked();

    void on_yesBtn_2_clicked();

    void on_noBtn_2_clicked();

    void on_homeBtn_2_clicked();

    void on_restartBtn_2_clicked();

    void on_returnBtn_4_clicked();

private:
    Ui::MainWindow *ui;
    //数据管理器
    DataManager dataManager;

    //主场景
    QStackedWidget *scenes;
    GameScene *gameScene;

    //主场景中的子控件
    QLineEdit *userEidt;

    //用户名
    QString username;

    //排行榜数据
    QListWidgetItem rankingLabels[3][MAX_RANK];

    void init();
    void setAllSkinType(int s); //设置所有cell的皮肤类型
    bool updateRanking(GameRecord record); //更新排行榜
    void displayRanking(int mode); //显示排行榜

};
#endif // MAINWINDOW_H
