#include "mapgen.h"

double Mapgen::maxRandSugar = 10;
double Mapgen::minRandSugar = 3;
double Mapgen::maxStorSugar = 20;
int Mapgen::randCount = 30;
Mapgen::Mapgen(){

}

int Mapgen::mtime()
{
    struct timeb timer;
    ftime(&timer);
    //return timer.time * 1000 + timer.millitm;
    return timer.time + timer.millitm;
}

int Mapgen::genMap(int size){
    //现在是均匀随机生成的地图格点，后期可以考虑改进地图生成，将糖集中在某一块正态分布
    default_random_engine e(mtime());
    uniform_int_distribution<int> intRandom(0,size-1);
    uniform_real_distribution<double> doubleRandom(minRandSugar, maxRandSugar);
    
    int x,y;
    double sugar;
    map.resize(size);
    for (int i=0; i<size; i++){
        map[i].resize(size);
    }

    for(int i=0; i<randCount; i++){
        x = intRandom(e);
        y = intRandom(e);
        sugar = doubleRandom(e);
        //重复选中的格子直接叠加
        map[x][y].sugar += sugar;
        //恢复速度设定
        map[x][y].recSpeed += sugar/7.0;
    }
    return 0;
}

int Mapgen::wormCome(int x,int y,int id){
    map[x][y].isOccupied = true;
    map[x][y].wormId = id;
    return 0;
}
int Mapgen::wormLeave(int x,int y){
    map[x][y].isOccupied = false;
    map[x][y].wormId = -1;
    return 0;
}

int Mapgen::sugarRec(){
    for(int i=0; i<map.size(); i++){
        for(int j=0; j<map.size(); j++){
            if(map[i][j].sugar < maxStorSugar)
            map[i][j].sugar += map[i][j].recSpeed;
            if(map[i][j].sugar > maxStorSugar)
            map[i][j].sugar = maxStorSugar;
        }
    }
    return 0;
}
