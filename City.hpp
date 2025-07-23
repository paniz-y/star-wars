#ifndef CITY.HPP
#define CITY .HPP
#include <utility>

class City
{
public:
    City(std::pair<int, int> coords, int spy);
    void setCoordinates(int x, int y);

    std::pair<int, int> getCoordinates();

    void setNumOfSpys(int spys);

    int getNumOfSpys();

protected:
    std::pair<int, int> coordinates;
    int numOfSpys;
};
#endif
