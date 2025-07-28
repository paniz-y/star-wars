#include "EnemyCity.hpp"

EnemyCity::EnemyCity(std::pair<int, int> coords, bool spy, Defense defenseForEnemyCity, bool defenceCheck) : City(coords, spy)
{
    defense = defenseForEnemyCity;
    setDefence(defenceCheck);
}

Defense EnemyCity::getDefense()
{
    return Defense();
}


