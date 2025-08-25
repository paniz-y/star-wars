#ifndef DEFENSE_HPP
#define DEFENSE_HPP
#include <utility>
class Defense
{
public:
    Defense();
    void setRatio(int ratio);
    int getRatio() const;
    void defend();
    ~Defense();

private:
    std::pair<int, int> coordinatesForDefense;
    int defenseRatio;
};

#endif