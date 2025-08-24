#ifndef ENEMYCITY_HPP
#define ENEMYCITY_HPP
#include <vector>
#include <tuple>
#include "City.hpp"
#include "Defense.hpp"

class EnemyCity : public City
{
public:
    EnemyCity(std::pair<int, int> coords, bool spy, Defense defense, bool defenceCheck);
    const Defense &getDefense() const;
    Defense &defenseForChange();
    bool getHasDefense() const override;
    void setDefense(bool defense) override;
    void setDefenseForRatio(int ratio);

private:
    Defense defense;
};

#endif