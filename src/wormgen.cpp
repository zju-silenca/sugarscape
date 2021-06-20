﻿#include "wormgen.h"

double Wormgen::minConsum = 0.5;
double Wormgen::moveConsum = 1;
double Wormgen::dayMaxSugar = 5;
double Wormgen::maxSugar = 10;
int Wormgen::crossWayCount = 0;
double Wormgen::bornLine = -1;//繁殖水平线
double Wormgen::bornConsum = 0.7;//繁殖消耗比例

Wormgen::Wormgen(){

}

int Wormgen::genWorm(int num){
    default_random_engine e(mtime()+num+map.size());
    uniform_int_distribution<int> intRandom(0,map.size()-1);
    uniform_int_distribution<int> wormRandom(0,num-1);
    //uniform_real_distribution<double> doubleRandom(0, 20);
    worm.resize(num);
    int x,y;
    for(int i=0; i<num; i++){
        x = intRandom(e);
        y = intRandom(e);
        while(map[x][y].isOccupied){
            x = intRandom(e);
            y = intRandom(e);
        }
        worm[i].x = x;
        worm[i].y = y;
        map[x][y].isOccupied = true;
        map[x][y].wormId = i;
    }

    for(int i=0; i<crossWayCount; ){
        int id = wormRandom(e);
        if(worm[id].moveWay == 0)
        {
            worm[id].moveWay = 1;
            i++;
        }
    }

    return 0;
}

int Wormgen::buryWorm(int id){
    grave.push_back(worm[id]);
    worm[id].sugar = 0;
    worm[id].live = false;
    wormLeave(worm[id].x,worm[id].y);
    return 0;
}

int Wormgen::daysConsum(int id){
    if(worm[id].live)
    worm[id].sugar -= minConsum;
    else
    return 0;

    if(worm[id].sugar <= 0)
    buryWorm(id);
    return 0;
}

int Wormgen::eatSugar(){
    //不超过Max，不能吃到负
    double eatCount = 0;
    int id;
    for(int i=0; i<worm.size(); i++){
        id = i;
        if(!worm[id].live)
        continue;

        if(maxSugar - worm[id].sugar < dayMaxSugar){
            eatCount = maxSugar - worm[id].sugar;
        }else{
            eatCount = dayMaxSugar;
        }

        if(eatCount > map[worm[id].x][worm[id].y].sugar){
            eatCount = map[worm[id].x][worm[id].y].sugar;
        }

        worm[id].sugar += eatCount;
        map[worm[id].x][worm[id].y].sugar -= eatCount;
    }
    return 0;
}

int Wormgen::bornWorm(int id)
{
    if(worm[id].sugar < bornLine || bornLine <= 0)
        return 0;
    default_random_engine e(mtime()+id+map.size());
    uniform_int_distribution<int> intRandom(0,1);
    int targetX, targetY,i=0;
    do{
        if(intRandom(e)){
            if(intRandom(e)){
                targetX = worm[id].x + 1;
                targetY = worm[id].y;
            }else{
                targetX = worm[id].x - 1;
                targetY = worm[id].y;
            }
        }else{
            if(intRandom(e)){
                targetY = worm[id].y + 1;
                targetX = worm[id].x;
            }else{
                targetY = worm[id].y - 1;
                targetX = worm[id].x;
            }
        }
        i++;
        if(i>=10)//防止死循环
        {
            return 0;
        }
    }while (targetX < 0 || targetX >= map.size()
            || targetY < 0 || targetY >= map.size()
            || map[targetX][targetY].isOccupied);

    wormdata newWorm = {
        targetX,targetY,
        worm[id].sugar*bornConsum,
        0,
        worm[id].moveWay,
        true
    };

    worm[id].sugar -= worm[id].sugar*bornConsum;
    worm.push_back(newWorm);
}
