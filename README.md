# MineSweeper扫雷
My production in the course "Programming Practice-1" implemented with c++ and Qt

## 0. 声明

- 本作品为编程实践的课设，使用c++和Qt实现可视化界面
- 欢迎各位参考本作品，若在使用过程中发现了Bug，可提出issue，~~虽然我也不一定会改~~
- 本作品的界面布局参考了游戏Fmine（扫雷F），这是一款非常精美、好玩的游戏，已在taptap上架
- 本作品中的图片素材来自于Fmine，阿里巴巴矢量图标库和视觉中国

## 1. 游戏方式

- 左键点击一个格子可打开改格子。若打开了地雷，则游戏失败；若打开了所有不含地雷的格子，则游戏胜利
- 右键点击一个格子可标记或取消标记旗子。游戏界面上方有可用旗子数，初始可用旗子数等于总地雷数
- 左右键同时点击一个格子，且该格子周围的地雷数等于旗子数时，可打开周围未被旗子标记的格子

## 2. 游戏介绍

- 主界面：游戏的主界面，可通过按钮登录用户名、开始游戏、更换皮肤和查看排行榜![image-20220914224947934](https://github.com/LucasWang03/MineSweeper/blob/main/img/image-20220914224947934.png)
- 难度选择：一共有简单、普通、苦难和自定义四个难度可供选择![image-20220914225521994](https://github.com/LucasWang03/MineSweeper/blob/main/img/image-20220914225521994.png)

- 更换皮肤：一共有默认、灰金和晴空三种皮肤可任意切换![image-20220914225831510](https://github.com/LucasWang03/MineSweeper/blob/main/img/image-20220914225831510.png)

- 排行榜：分别对三种游戏难度进行游戏胜利时长的排行，并记录到rank.dat文件里（**注意必须点击退出按钮才能保存游戏记录，关闭窗口则无法保存**）![image-20220914230102272](https://github.com/LucasWang03/MineSweeper/blob/main/img/image-20220914230102272.png)

## 3. 总结

经历了整整十天的折磨，终于是写完了这个扫雷游戏（~~其实主界面还有个成就系统，不过我是真不想写了~~）。先是只花了四天初略地浏览了一遍c++和Qt，然后又一个人只花了五天写完这个游戏，我记得最后一天晚上我真的是浑身酸软无力、脑袋发懵，然而还不得不写项目开发文档和实训心得体会，还要做答辩PPT，算是体验了一把8117，一定要run出去逃离996啊（悲）。

本项目的代码量和类都很少，因为界面设计都通过ui designer来完成，最后呈现出来的效果还挺让我满意的，另外也正是因为类少，我认为游戏的主体逻辑还是比较清晰的，各位想写扫雷项目的话可以进行参考，但是更换皮肤和排行榜功能都糅杂在mainwindow.cpp/ui里面了，因为时间太短来不及设计整体框架了，各位在实现这些功能的时候可以将代码模块化一下，可能会更便于阅读、debug和修改。

嗯，就是这样，另外我还上传了exe的压缩包，感兴趣的话可以下载进行游玩，可以的话请给个star吧！
