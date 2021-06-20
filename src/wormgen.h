﻿/*虫生成类，负责记录管理每个虫子的数据，管理生命周期
*/
#include "mapgen.h"

class Wormgen : public Mapgen{
private:
    struct wormdata{
        int x,y;
        double sugar = 10;
        int steps = 0;
        int moveWay = 0; //移动策略
        bool live = true;
    };

public:

    Wormgen();
    vector <wormdata> worm;
    //墓地
    vector <wormdata> grave;
    //虫子各消耗参数
    static double minConsum;//每天最低消耗
    static double moveConsum;//每次移动消耗
    static double maxSugar;//能存储最大糖量
    static double dayMaxSugar;//每天最大摄入糖量
    static int crossWayCount;//增强移动策略虫子数量
    static double bornLine;//繁殖水平线
    static double bornConsum;//繁殖消耗

    //生成虫子
    int genWorm(int);
    //将指定id虫子移入墓地
    int buryWorm(int id);
    //扣去指定id的每日消耗
    int daysConsum(int id);
    //扣除所有虫子的每日消耗
    int eatSugar();

    //繁殖
    int bornWorm(int id);
    
};
