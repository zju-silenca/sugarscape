#include "result.h"
#include <iostream>
#include <iomanip>

int Result::printWormState(int id){

    cout << setw(coutWidth) << id;
    cout << setw(coutWidth) << worm[id].sugar;
    cout << setw(coutWidth) << worm[id].steps;
    if(worm[id].live){
        cout << setw(coutWidth) << "live" << endl;
    }else{
        cout << setw(coutWidth) << "dead" << endl;
    }
    return 0;
}

int Result::printAllWormState(){
    int num ;
    cout << setw(coutWidth) << setiosflags(ios::left) << "ID";
    cout << setw(coutWidth+2) << "糖量";
    cout << setw(coutWidth+2) << "步数";
    cout << setw(coutWidth+2) << "状态" << endl;
    num = worm.size();
    for(int i=0; i<num; i++){
        printWormState(i);
    }
    return 0;
}

int Result::printLiveWormState(){
    int num ;
    cout << setw(coutWidth) << setiosflags(ios::left) << "ID";
    cout << setw(coutWidth+2) << "糖量";
    cout << setw(coutWidth+2) << "步数";
    cout << setw(coutWidth+2) << "状态" << endl;
    num = worm.size();
    for(int i=0; i<num; i++){
        if(worm[i].live)
        printWormState(i);
    }
    return 0;
}

int Result::printDeadWormState(){
    int num ;
    cout << setw(coutWidth) << setiosflags(ios::left) << "ID";
    cout << setw(coutWidth+2) << "糖量";
    cout << setw(coutWidth+2) << "步数";
    cout << setw(coutWidth+2) << "状态" << endl;
    num = worm.size();
    for(int i=0; i<num; i++){
        if(!worm[i].live)
        printWormState(i);
    }
    return 0;
}