#ifndef DEFENSE_HPP
#define DEFENSE_HPP
#include <vector>

class Defense
{
public:
    Defense();
    void setRatio(int ratio);
    int getRatio();
   
private:
    std::pair<int, int> coordinatesForDefense;
    int defenseRatio;
};

#endif