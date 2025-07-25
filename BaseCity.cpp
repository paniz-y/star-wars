#include "BaseCity.hpp"
BaseCity::BaseCity(std::pair<int, int> coords, bool spy, std ::vector<std::shared_ptr<Spaceship>> spaceships) : City(coords, spy)
{
    listOfSpaceships = spaceships;
}
// BaseCity::BaseCity(){}
void BaseCity ::setListOfSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships)
{
    listOfSpaceships = spaceships;
}
std::vector<std::shared_ptr <Spaceship>> BaseCity ::getListOfSpaceships()
{
    return listOfSpaceships;
}
