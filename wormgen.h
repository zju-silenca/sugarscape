/*虫生成类，负责记录管理每个虫子的数据，管理生命周期
*/
#include <mapgen.h>

class Wormgen : public Mapgen{
private:
    struct wormdata{
        int x,y;
        double sugar = 10;
        int steps = 0;
        bool live = true;
    };

public:
    vector <wormdata> worm;
    //回收死亡虫子
    vector <wormdata> grave;
    //虫子各消耗参数
    double minConsum = 0.5;//每天最低消耗
    double moveConsum = 1;//每次移动消耗
    double maxSugar = 20;//能存储最大糖量
    double dayMaxSugar = 5;//每天最大摄入糖量
    
    int genWorm(int);
    int buryWorm(int id);
    int daysConsum(int id);
    int eatSugar();
    
};