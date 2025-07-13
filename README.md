# C++大作业（地牢冒险游戏）
包括了移动、与NPC互动、攻击敌人等功能



-2025/7/12/11:24

本次更新了游戏的进入界面，新增商店的武器贴图和失败界面

-2025/7/13

增加了类 Win 接入胜利入口

增加了类 Failed接入失败入口

在 Hero 类和 HeroMoveAttribute 类中增加了判断胜利的接口:

​	-Hero.win(int end) ; HeroMoveAttribute.win();

在MapList类的AddEnermy、 addBarrier、addShopman 中增加了判定是否超出右边界的判断

​	增加了len表示地图长度

​	将screen_x由引用，改为实参

在主函数中添加了最后界面的背景图；

​    增加了多地图设计。

​	更新了商店UI的武器、人物属性显示。
