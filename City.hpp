#ifndef CITY.HPP
#define CITY .HPP
#include <utility>

class City
{
public:
    void setCoordinates(int x, int y);

    std::pair<int, int> getCoordinates();

    void setSpyExists();

    void setSpyDoesNotExist();

    bool getSpyExistence();

protected:
    std::pair<int, int> coordinates;
    bool spyExistence;
};
#endif
