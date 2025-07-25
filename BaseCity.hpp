#ifndef BASECITY_HPP
#define BASECITY_HPP
#include <vector>
#include "City.hpp"
#include "Spaceship.hpp"

class BaseCity : public City
{
public:
    // BaseCity();
    BaseCity(std::pair<int, int> coords, bool spy, std ::vector<Spaceship> spaceships);
    void setListOfSpaceships(std::vector<Spaceship> spaceships);
    std::vector<Spaceship> getListOfSpaceships();
    int programSpaceship(Spaceship spaceship);

private:
    std ::vector<Spaceship> listOfSpaceships;
};

#endif