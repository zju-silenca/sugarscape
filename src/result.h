#include "wormmove.h"

class Result : public Wormmove{
private:
    //打印宽度
    int coutWidth = 10;

public:
    //打印单个虫子的状态
    int printWormState(int id);
    //打印虫子状态
    int printAllWormState();
    int printLiveWormState();
    int printDeadWormState();
};
