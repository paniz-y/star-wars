#include "City.hpp"

City::City(std::pair<int, int> coords, int spy)
{
    coordinates = coords;
    spyExistence = spy;
}

void City::setCoordinates(int x, int y)
{
    coordinates.first = x;
    coordinates.second = y;
}
std::pair<int, int> City::getCoordinates()
{
    return coordinates;
}
void City::setExistingSpy(bool spy)
{
    spyExistence = spy;
}

bool City::getExistenceOfSpy()
{
    return spyExistence;
}

bool City::getHasDefense() const
{
    return hasDefense;
}
void City::setDefense(bool defense)
{
    hasDefense = defense;
}
