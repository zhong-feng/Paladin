#include "CDrug.h"


CDrug::~CDrug()
{

}

CDrug::CDrug()
{
    type = IT_Drug;  //类型是 IT_Drug

    count = 99; // 可以叠加 99 个 

    hp = 0;
    mp = 0;
}
