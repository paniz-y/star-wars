#include "City.hpp"

City::City(std::pair<int, int> coords, int spy)
{
    coordinates = coords;
    spyExistence = spy;
}
// City::City(){}

void City::setCoordinates(int x, int y)
{
    coordinates.first = x;
    coordinates.second = y;
}
std::pair<int, int> City::getCoordinates()
{
    return coordinates;
}
void City::setExistingSpys(bool spy)
{
    spyExistence = spy;
}

bool City::getExistenceOfSpy()
{
    return spyExistence;
}
