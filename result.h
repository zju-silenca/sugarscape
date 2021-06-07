#include "wormmove.h"

class Result : public Wormmove{
private:
    int coutWidth = 10;

public:
    int printWormState(int id);
    int printAllWormState();
    int printLiveWormState();
    int printDeadWormState();
};