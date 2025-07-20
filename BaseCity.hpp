#ifndef BASECITY.HPP
#define BASECITY .HPP
#include "City.hpp"
#include "Spaceship.hpp"
#include <vector>
class BaseCity : public City
{
public:
    void setListOfSpaceships(std::vector<Spaceship> spaceships);
    std::vector<Spaceship> getListOfSpaceships();
    int programSpaceship(Spaceship spaceship);

private:
    std ::vector<Spaceship> listOfSpaceships;
};

#endif