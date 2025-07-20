#include "City.hpp"

void City::setCoordinates(int x, int y)
{
    coordinates.first = x;
    coordinates.second = y;
}
std::pair<int, int> City::getCoordinates()
{
    return coordinates;
}
void City::setSpyExists()
{
    spyExistence = true;
}
void City::setSpyDoesNotExist()
{
    spyExistence = false;
}
bool City::getSpyExistence()
{
    return spyExistence;
}
