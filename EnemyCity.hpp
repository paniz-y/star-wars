#ifndef ENEMYCITY_HPP
#define ENEMYCITY_HPP
#include <vector>
#include "City.hpp"
#include "Defense.hpp"

class EnemyCity : public City
{
public:
    // BaseCity();
    EnemyCity(std::pair<int, int> coords, bool spy,Defense defense);
    // void setListOfSpaceships(std::vector<Spaceship> spaceships);
    // std::vector<Spaceship> getListOfSpaceships();
    // int programSpaceship(Spaceship spaceship);

private:
    Defense defenseRatio;
};

#endif