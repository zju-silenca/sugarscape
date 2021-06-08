#include "result.h"
#include <iostream>
using namespace std;
class Sugarscape :public Result{
private:
    //模拟天数
    int allDays;
public:
    //模拟入口
    int simulateDays(int days);
    ~Sugarscape();
    //重置所有状态
    void resetState();
};

class Qtapi : public Sugarscape{
    //生成对象供Qt使用
public:
    Sugarscape obj;
    Sugarscape obj2;
};
