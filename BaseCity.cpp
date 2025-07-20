#include "BaseCity.hpp"

void BaseCity ::setListOfSpaceships(std::vector<Spaceship> spaceships)
{
    listOfSpaceships = spaceships;
}
std::vector<Spaceship> BaseCity ::getListOfSpaceships()
{
    return listOfSpaceships;
}
