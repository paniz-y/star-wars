#include "EnemyCity.hpp"

EnemyCity::EnemyCity(std::pair<int, int> coords, bool spy, Defense defenseForEnemyCity, bool defenceCheck) : City(coords, spy)
{
    defense = defenseForEnemyCity;
    setDefense(defenceCheck);
}

Defense EnemyCity::getDefense()
{
    return defense;
}

bool EnemyCity::getHasDefense() const
{
    return hasDefense;
}

void EnemyCity::setDefense(bool defense)
{
    hasDefense = defense;
}
