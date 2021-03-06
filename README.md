# 混乱大枪战 项目文档

> 同济大学软件学院2022年高级程序设计（荣）课程项目

## 一、项目信息

- 项目选题：混乱大枪战
- 项目GitHub地址：https://github.com/TJURoll/Gun-Mayhem

### 项目成员 && 贡献占比

---

| 姓名   | 学号    | 贡献比 以平均值为100% | 贡献比 以总分为100% | 班级   |
| ------ | :------ | --------------------- | ------------------- | ------ |
| 宋奕欣 | 2152058 | 100%                  | 25%                 | 朱老师 |
| 陈雨彤 | 2153677 | 100%                  | 25%                 | 朱老师 |
| 李锦霖 | 2152970 | 100%                  | 25%                 | 朱老师 |
| 刘启航 | 2151269 | 100%                  | 25%                 | 朱老师 |

### 分工

---

| 组员   | 完成项                                                       |
| :----- | ------------------------------------------------------------ |
| 宋奕欣 | 统筹规划类的设计、完成初始界面、实现各类监听、宝箱掉落、实现武器类、修改玩家类 |
| 陈雨彤 | 实现设置、暂停、结果、房间场景，撰写项目文档，制作答辩ppt，readme文档 |
| 李锦霖 | 游戏地图设计、引入物理引擎、尝试移植入Android                |
| 刘启航 | 实现玩家类、实现AI类、人物形象设计、部分接口的连接           |

### **项目进度时间线**

---

| 日期                | 功能                                                |
| ------------------- | --------------------------------------------------- |
| 2022.4.23~2022.5.04 | 学习cocos2dx，搭建环境，建立仓库                    |
| 2022.5.05~2022.5.15 | 完成初始界面和类框架，学习Github，素材收集          |
| 2022.5.16~2022.5.24 | 完成游戏地图，实现类（玩家、敌军、武器）            |
| 2022.5.25~2022.6.01 | Debug、实现背景音乐及音效、实现武器效果             |
| 2022.6.01~2022.6.08 | Debug、实现设置、暂停、结果、房间的场景功能，实现AI |
| 2022.6.08~2022.6.12 | Debug、撰写项目文档、制作答辩ppt                    |

## 二、**游戏整体架构设计**

我们将游戏拆分为五个部分：基本场景、游戏场景、玩家、AI、武器。

基本场景的架构为：背景、按钮、音乐音效。

游戏场景的架构为：物理世界构建、武器掉落、监听（射击碰撞监听、人物移动监听）。

玩家类的架构为：键盘鼠标监听、物理引擎、动作（跳跃、行走）、射击。

AI类的架构为：玩家定位、移动、射击。

武器类架构为：枪支（手枪、狙击枪、机枪）、子弹、炸药。

各部分间通过场景切换、类的接口等来连接组合。

## 三、**实现的功能点+实现思路**

### 3.1 **实现的功能点**

●游戏开始界面、背景音乐、音量控制、暂停及恢复功能、退出功能

●创建房间以及进入房间功能，支持添加 AI 

●武器系统，至少实现手枪、狙击枪、机枪三种不同武器以及特殊武器炸药包。不同武器有不同的攻击效果。

●武器掉落功能，可通过拾取掉落的宝箱获取不同武器

●键盘实现人物走动和跳动，鼠标实现枪械攻击和炸药攻击

●无限生命

●攻击和爆炸的特效

●计时系统

●暴击与命中显示

●计分与排行榜

###  3.2 实现思路

●基本场景的思路：主要由Scene、spirit（button、label）等cocos2dx的类及函数完成。建立场景类，往场景中addChild精灵。

●游戏场景的思路：用cocos自带的物理引擎来模拟地图的场景、给人物加上物理引擎。

●玩家类思路：对于人物移动以及鼠标按动接口，采取的是监视器+update函数+map记录连续按键的方式进行实现，后期，优化时，部分单独函数实现改成使用lambda表达式的形式进行实现，增强了程序效率。对于人物移动和跳跃，采用moveby动画予以逐步实现。

● AI类思路：动态检测玩家动态，且在update函数中调用monster类中类似update函数进行回应。

●武器类思路：把射击和扔炸药作为成员函数放入武器基类。为了实现不同枪的不同参数，在武器基类里设置了相应的成员变量，利用派生的武器派生类的构造函数为基类变量赋值。为了实用简便，采用create方法生成武器派生类，然后向上转型直接把其赋给武器基类变量，并通过bindShooter纯虚函数加入武器持有者的Child中。

## 四、**项目的技术难点+解决方案与解决过程**

### 4.1 **实现人物连续移动**

技术难点：一开始人物移动的时候移动需要不停的按键才能连续的移动。

解决方案：使用updata解决。

### 4.2 **实现人物平滑跳跃**

技术难点：人物和平台之间的碰撞使游戏里人物的动作变得不正常

解决方案：跳跃过程采用Sequence动作序列，先把任务碰撞比特掩码设为0000再执行moveby然后恢复，防止与地面穿模碰撞引起的跳跃不流畅的问题

### 4.3 素材获取

技术难点：获取素材较为艰难，之前初代demo,我们曾经尝试用一些网络图片来还原真实游戏场景，然而还原程度不高，游戏体验不佳。一些非矩形按钮需要抠图和透明背景。

解决方案：在网络上获取swf文件之后，采取了flash decompiler进行了逆编译，获取了有关的图形资源。利用抠图小程序，生成.png文件，即可显示透明背景的不规则形状。

### 4.4 **AI的跳跃设计**

技术难点：对于跳跃而言，跳跃时间、跳跃长度、刷新时间将紧密影响整体的实现。倘若设置有误，会出现人物上下正弦摆动，亦或是无法跳跃到上一级阶梯的情况。

解决方案：反复调试。

### **4.5 背景音乐切换与控制**

技术难点：本项目中采用了两款音乐，一是菜单界面的音乐，二是对战界面的音乐。由于游戏中存在反复的场景切换，音乐的控制很容易出现音量显示与实际不一致，背景音乐重叠的问题

解决方案：经过不断测试发现，audio类中自带的暂停播放等函数并不适合于复杂的音乐控制，最终采用很多对音量进行读取和设置的方法来实现音乐的停止播放的效果，此外，为了实现显示与实际情况的统一对音乐的播放状态采用了很多严谨的逻辑判断。

### **4.6 碰撞与接触信息的比特掩码体系构建**

技术难点：GameScene场景内涉及大量对象，包括地面、我方角色和子弹、地方角色和子弹、箱子、炸弹，每一类对象的三个比特掩码都有严格要求，比如敌我子弹之间不能碰撞，我方子弹不能与敌人碰撞等等。这些严格的条件给比特掩码的设定带来了很大难度。

解决方案：组长设计了一套完整的比特掩码表，小组内各个成员依照该表给自己设计的对象添加对应的比特掩码，防止冲突。

### **4.7** **场景之间的参数传递**

技术难点：游戏的胜利与否、AI的数量、是否无限生命需要场景间传参，如何合理使用全局变量是一个难点

解决方案：在Global.cpp中定义全局变量，在Global.h中进行extern声明，需要改全局变量的场景只需要include这一头文件即可，在使用全局变量中我们严格减少了全局变量个数和获取到全局变量的文件个数

 

## **五、**亮点部分

### **5.1 StartScene的设计**

采用buttonCreate和buttonAdd函数对菜单按钮进行创建和添加，buttonCreate减少了菜单中多个有相同形状、贴图的按钮创建时的代码重复，buttonAdd实现了任意数量的按钮添加到场景中的过程，便于之后增提案菜单按钮，提高代码的可维护性。两个函数中用到了迭代器、vector容器、lambda表达式（且转化为函数指针）、auto类型推断的c++特性。

### **5.2 AI的实现**

#### **5.2.1 单AI**

对于 AI的制作，此时采用的是动态检测玩家动态，且在update函数中调用monster类中类似update函数进行回应，在单AI时，AI将根据玩家的位置，实现对玩家的逐步靠近，与变换方向功能，并且由于整个游戏地图边界成阶梯状分布，此时我们采用了动画结合的方式，当判断人物处于阶梯的边缘且有上跳的需求的时候，我们将采取上跳与左移动画结合的方式，实现人物斜上跳动画。倘若角色检测到满足射击要求，角色会主动射击。整个程序中还设置了闪避函数，AI将在受到攻击后自动闪避，以减少被连击。

#### **5.2.1 双AI**

对于双AI的制作，不仅仅是1+1=2那样，整体双AI的制作，为了避免出现延迟，此时我们重新设计了一个函数进行实现，整体而言，双AI在原先单AI的基础上，增加了包抄功能，并且对于之前攻击移动的细节有着一定的优化，于此同时，双AI的话，倘若其中1个AI出现被消灭的情况，其能及时将其移出场景，并且保证游戏不出现崩溃。此外，为了丰富游戏趣味性，在双AI时，倘若玩家已经消灭了一个AI，且剩余AI生命值为1的时候，有概率出现游戏双方“肉搏”画面，此时玩家需要小心将AI推下场景，才能取得最终的胜利。

### **5.3 调试工作**

GameScene之中需要进行大量的调试，为了调试的方便，我们采用了编译预处理指令（宏定义DEBUG表示调试状态，直接进入GameScene场景），同时在碰撞的调试过程中打印出碰撞双方的Tag，有利于效率的提高和问题的发现。

### **5.**4 **版本控制与团队协作**

全程使用GitHub和Git进行版本控制

### **5.5 运用C++11及以上特性**

初始化列表、类型推断、基于范围的for循环、常量表达式、Lambda表达式

### **5.6 其他**

界面精致、没有内存泄露、程序几乎不会出现崩溃

## **六、游戏文档**

### 游戏简介

---

混乱大枪战是一款战术枪击类游戏。玩家可与1或2个AI玩家在地图上，通过移动、跳跃、射击、炸弹、捡宝箱获取新武器，射落对手，来获得胜利。

### **操作**

---

| 键           | 动作 |
| ------------ | ---- |
| 鼠标左键单击 | 射击 |
| 鼠标左键按住 | 炸药 |
| W键          | 上移 |
| A键          | 左移 |
| S键          | 下移 |
| D键          | 右移 |
| P键          | 暂停 |

## **模式**

---

### 生命数量

- 生命有限模式：5条命

- 生命无限模式：在Room界面勾选

### AI数量

- AI*1：默认
- AI*2：在Room界面按点击灰色的AI头像，若出现红色AI人物，则表示为双AI模式。

### 武器种类与属性

---

| 武器名                     | 射击间隔 | 伤害 | 子弹速度 |
| -------------------------- | -------- | ---- | -------- |
| Machine Gun       机械枪   | 0.05     | 3    | 3000     |
| Hand Gun            手枪   | 0.3      | 8    | 2000     |
| Sniper Gun          狙击枪 | 0.6      | 15   | 5000     |

## 输赢判定

在生命有限模式中，玩家方与AI方，哪方先掉落地图**5**次，即判定为输方。

## 游戏界面

除场景和人物外：游戏界面的左上方为我方玩家的生命条数，右上方为游戏开局时长。

## 排行榜

将在主界面自动保存三个最好的成绩，包括玩家、时间和系统生成的分数。

## 联系我们

> 宋奕欣 [552405935@qq.com](mailto:552405935@qq.com)
>
> 陈雨彤 [2472091566@qq.com](mailto:2472091566@qq.com)
>
> 李锦霖 [2432537836@qq.com](mailto:2472091566@qq.com)
>
> 刘启航 [2478167310@qq.com](mailto:2478167310@qq.com)