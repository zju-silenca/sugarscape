/*虫移动类
*/

#include "wormgen.h"

class Wormmove : public Wormgen{
private:
    int targetX, targetY;


public:

    //获取附近目标
    int getNearTarget(int id);//成功后返回移动策略数字代号
    int getNearTarget1(int id);//周围四格
    int getNearTarget2(int id);//四方各向外延伸一格
    //随机一个目标
    int getRandomTarget(int id);
    //指定id虫子移动
    int wormMove(int id);
    //所有虫子移动
    int allWormMove();

    //用于虫单个移动探究路径
    int singleMove(int num);

};
