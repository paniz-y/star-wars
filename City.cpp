#include "City.hpp"

City::City(std::pair<int, int> coords, int spy)
{
    coordinates = coords;
    numOfSpys = spy;
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
void City::setNumOfSpys(int spys)
{
    numOfSpys = spys;
}

int City::getNumOfSpys()
{
    return numOfSpys;
}
