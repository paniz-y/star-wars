#include "EnemyCity.hpp"

EnemyCity::EnemyCity(std::pair<int, int> coords, bool spy, Defense defense) : City(coords, spy)
{
    defenseRatio = defense;
}