#include "Defense.hpp"

Defense::Defense(){}
void Defense::setRatio(int ratio)
{
    defenseRatio = ratio;
}
int Defense::getRatio()
{
    return defenseRatio;
}

void Defense::defend()
{
    defenseRatio--;
}
