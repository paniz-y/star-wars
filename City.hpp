#ifndef CITY_HPP
#define CITY_HPP
#include <utility>
#include <memory>
class City
{
public:
    City(std::pair<int, int> coords, int spy);
    void setCoordinates(int x, int y);

    std::pair<int, int> getCoordinates();

    void setExistingSpys(bool spy);

    bool getExistenceOfSpy();
    bool getHasDefence();
    void setDefence(bool);
    // bool operator==(const City& otherCity) const 
    // {
    //     return coordinates == otherCity.coordinates && spyExistence == otherCity.spyExistence;
    // }

protected:
    std::pair<int, int> coordinates;
    bool spyExistence;
    bool hasDefense;
};
#endif
