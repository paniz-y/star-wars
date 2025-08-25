#ifndef ENEMYCITY_HPP
#define ENEMYCITY_HPP
#include <vector>
#include <tuple>
#include "City.hpp"
#include "Defense.hpp"

class EnemyCity : public City
{
public:
    EnemyCity(std::pair<int, int> coords, bool spy, Defense defense);
    const Defense &getDefense() const;
    Defense &defenseForChange();
    int getCapacity() const override;
    void setDefenseForRatio(int ratio);
    ~EnemyCity() override;

private:
    Defense defense;
};

#endif