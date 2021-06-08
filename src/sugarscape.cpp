#include "sugarscape.h"
#include <iostream>
using namespace std;


//int main(){
//    Sugarscape obj;
//    obj.genMap(20);
//    obj.genWorm(10);
//    //vector <int> Id;
//    cout << "请输入天数" <<endl;
//    int days;
//    cin >>days;
//    obj.simulateDays(days);
//    cout << "死亡虫子列表：" << endl;
//    obj.printDeadWormState();
//    cout << "存活虫子列表：" << endl;
//    obj.printLiveWormState();
//    return 0;
//}

Sugarscape::~Sugarscape(){
}

int Sugarscape::simulateDays(int days){
    allDays = days;
    int numbers;
    numbers = worm.size();
    for(int i=0; i<days; i++){
        eatSugar();
        allWormMove();
        sugarRec();
    }
    return 0;
}

void Sugarscape::resetState(){
    map.clear();
    worm.clear();
    grave.clear();
}

