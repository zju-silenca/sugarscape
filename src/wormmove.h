/*虫移动类
*/

#include "wormgen.h"

class Wormmove : public Wormgen{
private:
    int targetX, targetY;


public:

    int getNearTarget(int id);
    int getRandomTarget(int id);
    int wormMove(int id);
    int allWormMove();
    //用于虫单个移动探究路径

    int singleMove(int num);

};
