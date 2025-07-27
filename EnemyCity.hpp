#ifndef ENEMYCITY_HPP
#define ENEMYCITY_HPP
#include <vector>
#include <tuple>
#include "City.hpp"
#include "Defense.hpp"

class EnemyCity : public City
{
public:
    // BaseCity();
    EnemyCity(std::pair<int, int> coords, bool spy, Defense defense);
    Defense getDefense();
    
    // void setListOfSpaceships(std::vector<Spaceship> spaceships);
    // std::vector<Spaceship> getListOfSpaceships();
    // int programSpaceship(Spaceship spaceship);
    // bool operator==(const EnemyCity otherEnemyCity) const {
    //     return (coordinates == otherEnemyCity.coordinates) && (spyExistence == otherEnemyCity.spyExistence) && (defense == otherEnemyCity.defense);
    // }
    // bool operator==(const EnemyCity otherEnemyCity) const
    // {
    //     return std::tie(coordinates, spyExistence, defense) == std::tie(otherEnemyCity.coordinates, otherEnemyCity.spyExistence, otherEnemyCity.defense);
    // }
    // bool operator==(const EnemyCity& otherEnemyCity) const 
    // {
    //     return City::operator==(otherEnemyCity)  && defense == otherEnemyCity.defense;
    // }

private:
    Defense defense;
};
// namespace std
// {
//     template <>
//     struct hash<EnemyCity>
//     {
//         size_t operator()(EnemyCity enemyCity) const
//         {
//             auto tuple = std::tie(static_cast<const City&>(enemyCity), enemyCity.getDefense().defenseRatio);
//             return std::hash<decltype(tuple)>()(tuple);
//         }
//     };
// }

#endif