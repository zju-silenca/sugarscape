#include "wormmove.h"

int Wormmove::getNearTarget(int id)
{
    if(worm[id].moveWay == 0)
        return getNearTarget1(id);
    if(worm[id].moveWay == 1)
        if(worm[id].sugar < 2*moveConsum)
            return getNearTarget1(id);
        return getNearTarget2(id);
    return 0;
}

int Wormmove::getNearTarget1(int id)
{
    double temp;
    int currentX, currentY, flag = 0;
    currentX = worm[id].x;
    currentY = worm[id].y;
    temp = map[currentX][currentY].sugar;

    if(currentX + 1 < map.size())
        if (temp < map[currentX + 1][currentY].sugar )
        {
            targetX = currentX + 1;
            targetY = currentY;
            if(map[targetX][targetY].isOccupied){
                targetX = currentX;
                targetY = currentY;
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
                targetX = currentX;
                targetY = currentY;
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
                targetX = currentX;
                targetY = currentY;
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
                targetX = currentX;
                targetY = currentY;
                flag = 0;
            }else{
            temp = map[targetX][targetY].sugar;
            flag = 1;           
            }

        }
    return flag;

}

int Wormmove::getNearTarget2(int id)
{
    double temp;
    int currentX, currentY, flag = 0;
    if(getNearTarget1(id))
    {
        currentX = worm[id].x;
        currentY = worm[id].y;
        temp = map[targetX][targetY].sugar;
        flag = 1;
    }else{
        currentX = worm[id].x;
        currentY = worm[id].y;
        temp = map[currentX][currentY].sugar;
    }


    if(currentX + 2 < map.size())
        if (temp < map[currentX + 2][currentY].sugar )
        {
            if(! map[currentX + 2][currentY].isOccupied){
                targetX = currentX + 2;
                targetY = currentY;
                temp = map[targetX][targetY].sugar;
                flag = 2;
            }
        }
    if(currentX - 2 >= 0)
        if (temp < map[currentX - 2][currentY].sugar )
        {
            if(! map[currentX - 2][currentY].isOccupied){
                targetX = currentX - 2;
                targetY = currentY;
                temp = map[targetX][targetY].sugar;
                flag = 2;
            }
        }
    if(currentY + 2 < map.size())
        if (temp < map[currentX][currentY + 2].sugar )
        {
            if(! map[currentX][currentY + 2].isOccupied){
                targetX = currentX;
                targetY = currentY + 2;
                temp = map[targetX][targetY].sugar;
                flag = 2;
            }
        }
    if(currentY - 2 >= 0)
        if (temp < map[currentX][currentY - 2].sugar )
        {
            if(! map[currentX][currentY - 2].isOccupied){
                targetX = currentX;
                targetY = currentY - 2;
                temp = map[targetX][targetY].sugar;
                flag = 2;
            }
        }
    return flag;
}

int Wormmove::getRandomTarget(int id){
    default_random_engine e(mtime()+id+targetX+targetY);
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

    daysConsum(id);
    //无足够糖量移动
    if(worm[id].sugar - moveConsum <= 0){
        worm[id].sugar = 0;
        worm[id].live = false;
        buryWorm(id);
        return 0;
    }

    //移动
    switch (getNearTarget(id)) {
        case 1:
        {
            worm[id].steps++;
            worm[id].sugar -= moveConsum;
            wormCome(targetX,targetY,id);
            wormLeave(worm[id].x,worm[id].y);
            worm[id].x = targetX;
            worm[id].y = targetY;
            break;
        }
        case 2:
        {
            worm[id].steps += 2;
            worm[id].sugar -= 2*moveConsum;
            wormCome(targetX,targetY,id);
            wormLeave(worm[id].x,worm[id].y);
            worm[id].x = targetX;
            worm[id].y = targetY;
            break;
        }
        default:
        {
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

    }

//    if(getNearTarget(id)){
//        worm[id].steps++;
//        worm[id].sugar -= moveConsum;
//        wormCome(targetX,targetY,id);
//        wormLeave(worm[id].x,worm[id].y);
//        worm[id].x = targetX;
//        worm[id].y = targetY;
//    }else{
//        if(getRandomTarget(id)){
//            worm[id].steps++;
//            worm[id].sugar -= moveConsum;
//            wormCome(targetX,targetY,id);
//            wormLeave(worm[id].x,worm[id].y);
//            worm[id].x = targetX;
//            worm[id].y = targetY;
//        }else{
//            //被围住
//            return 0;
//        }
//    }

    return 0;
}

int Wormmove::allWormMove(){
    for(int i=0; i<worm.size(); i++){
        wormMove(i);
    }
    return 0;
}

int Wormmove::singleMove(int num){
    default_random_engine e(mtime());
    uniform_int_distribution<int> intRandom(0,1);
    for(int i=0; i<num; i++){
        map[worm[0].x][worm[0].y].sugar += 1;
        do{
            if(intRandom(e)){
                if(intRandom(e)){
                    targetX = worm[0].x + 1;
                    targetY = worm[0].y;
                }else{
                    targetX = worm[0].x - 1;
                    targetY = worm[0].y;
                }
            }else{
                if(intRandom(e)){
                    targetY = worm[0].y + 1;
                    targetX = worm[0].x;
                }else{
                    targetY = worm[0].y - 1;
                    targetX = worm[0].x;
                }
            }
        }while(targetX < 0 || targetX >= map.size()
               || targetY < 0 || targetY >= map.size()
               || map[targetX][targetY].isOccupied);
        wormCome(targetX,targetY,0);
        wormLeave(worm[0].x,worm[0].y);
        worm[0].x = targetX;
        worm[0].y = targetY;
        worm[0].steps++;
    }
    return 0;
}
