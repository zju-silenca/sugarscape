﻿/*
地图随机生成类，负责生成地图，格点数据管理
*/
#include <vector>
#include <random>
#include <sys/timeb.h>

using namespace std;

class Mapgen{
private:
    struct mapdata
    {
        double sugar = 0;//糖量
        double recSpeed = 0;//恢复速度
        bool isOccupied = false;//是否被占用
        int wormId = -1;//占用虫子id
    };


public:

    vector<vector<mapdata>> map;
    Mapgen();
    //地图生成参数
    static double maxRandSugar;//最大随机糖量
    static double minRandSugar;//最小随机糖量
    static double maxStorSugar;//格点存储上限
    static int randCount;//随机次数
    //生成地图
    int genMap(int size);
    //毫秒级时间
    int mtime();
    //处理虫子进入离开
    int wormCome(int x,int y,int id);
    int wormLeave(int x,int y);
    //所有格点糖量回复
    int sugarRec();
};
