#include "wormmove.h"

int Wormmove::getNearTarget(int id)
{
    double temp;
    int currentX, currentY, flag = 0;
    currentX = worm[id].x;
    currentY = worm[id].y;
    temp = worm[id].sugar;

    if(currentX + 1 < map.size())
        if (temp < map[currentX + 1][currentY].sugar)
        {
            targetX = currentX + 1;
            targetY = currentY;
            if(map[targetX][targetY].isOccupied){
                flag = 0;
            }else{
            temp = map[targetX][targetY].sugar;
            flag = 1;           
            }
        }
    
    if(currentX - 1 >= 0)
        if (temp < map[currentX - 1][currentY].sugar )
        {
            targetX = currentX - 1;
            targetY = currentY;
            if(map[targetX][targetY].isOccupied){
                flag = 0;
            }else{
            temp = map[targetX][targetY].sugar;
            flag = 1;           
            }
        }
    if(currentY + 1 < map.size())
        if (temp < map[currentX][currentY + 1].sugar )
        {
            targetX = currentX;
            targetY = currentY + 1;
            if(map[targetX][targetY].isOccupied){
                flag = 0;
            }else{
            temp = map[targetX][targetY].sugar;
            flag = 1;           
            }
        }
    if(currentY - 1 >= 0)
        if (temp < map[currentX][currentY - 1].sugar )
        {
            targetX = currentX;
            targetY = currentY - 1;
            if(map[targetX][targetY].isOccupied){
                flag = 0;
            }else{
            temp = map[targetX][targetY].sugar;
            flag = 1;           
            }

        }
    return flag;

}

int Wormmove::getRandomTarget(int id){
    default_random_engine e(mtime()+id);
    uniform_int_distribution<int> intRandom(0,1);
    int i=0;

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
        break;
    }while (targetX < 0 || targetX >= map.size()
            || targetY < 0 || targetY >= map.size() 
            || map[targetX][targetY].isOccupied);
    if(i<10)
        return 1;
    else
        return 0;

}

int Wormmove::wormMove(int id)
{
    if(!worm[id].live){
        return 0;
    }
    //若当前糖分够消耗一天以上则不动扣除最低消耗
    if(map[worm[id].x][worm[id].y].sugar > minConsum){
        daysConsum(id);
        return 0;
    }
    //无足够糖量移动
    if(worm[id].sugar - moveConsum <= 0){
        worm[id].sugar = 0;
        worm[id].live = false;
        buryWorm(id);
        return 0;
    }
    //移动
    if(getNearTarget(id)){
        worm[id].steps++;
        worm[id].sugar -= moveConsum;
        wormCome(targetX,targetY,id);
        wormLeave(worm[id].x,worm[id].y);
        worm[id].x = targetX;
        worm[id].y = targetY;
    }else{
        if(getRandomTarget(id)){
            worm[id].steps++;
            worm[id].sugar -= moveConsum;
            wormCome(targetX,targetY,id);
            wormLeave(worm[id].x,worm[id].y);
            worm[id].x = targetX;
            worm[id].y = targetY;            
        }else{
            //被围住
            return 0;
        }
    }
    return 0;
}

int Wormmove::allWormMove(){
    for(int i=0; i<worm.size(); i++){
        wormMove(i);
    }
    return 0;
}
