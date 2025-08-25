#include "EnemyCity.hpp"

EnemyCity::EnemyCity(std::pair<int, int> coords, bool spy, Defense defenseForEnemyCity) : City(coords, spy)
{
    defense = defenseForEnemyCity;
}

const Defense &EnemyCity::getDefense() const
{
    return defense;
}

Defense &EnemyCity::defenseForChange()
{
    return defense;
}

int EnemyCity::getCapacity() const
{
    return defense.getRatio();
}

void EnemyCity::setDefenseForRatio(int ratio)
{
    defense.setRatio(ratio);
}

void EnemyCity::decrementCapacity()
{
    return; // to avoid the class become abstract
}

EnemyCity::~EnemyCity()
{}
