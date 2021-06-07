#include "result.h"
#include <iostream>
using namespace std;
class Sugarscape :public Result{
private:
    int allDays;
public:
    int simulateDays(int days);
    ~Sugarscape();
    void resetState();
};

class Qtapi : public Sugarscape{
public:
    Sugarscape obj;
    Qtapi();
};
