#include "BaseCity.hpp"
BaseCity::BaseCity(std::pair<int, int> coords, bool spy, std ::vector<Spaceship> spaceships): City(coords, spy), listOfSpaceships(spaceships)
{

}
void BaseCity ::setListOfSpaceships(std::vector<Spaceship> spaceships)
{
    listOfSpaceships = spaceships;
}
std::vector<Spaceship> BaseCity ::getListOfSpaceships()
{
    return listOfSpaceships;
}
