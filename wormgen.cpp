#include "wormgen.h"

int Wormgen::genWorm(int num){
    default_random_engine e(mtime());
    uniform_int_distribution<int> intRandom(0,map.size()-1);
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
    return 0;
}

int Wormgen::buryWorm(int id){
    grave.push_back(worm[id]);
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