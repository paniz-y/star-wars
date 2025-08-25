#include "BaseCity.hpp"
BaseCity::BaseCity(std::pair<int, int> coords, bool spy, std ::vector<std::shared_ptr<Spaceship>> spaceships) : City(coords, spy)
{
    listOfSpaceships = spaceships;
    baseSize = 0;
}
BaseCity::BaseCity(std::pair<int, int> coords, bool spy) : City(coords, spy) {}
void BaseCity ::setListOfSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships)
{
    listOfSpaceships = spaceships;
}
std::vector<std::shared_ptr<Spaceship>> BaseCity ::getListOfSpaceships()
{
    return listOfSpaceships;
}

int BaseCity::getCapacity() const
{
    return baseCapacity;
}

void BaseCity::setCapacity(int capacity)
{
    baseCapacity = capacity;
}

int BaseCity::getSize() const
{
    return baseSize;
}

void BaseCity::setSize(int size)
{
    baseSize = size;
}

void BaseCity::incrementSize()
{
    baseSize++;
}

BaseCity::~BaseCity()
{}
