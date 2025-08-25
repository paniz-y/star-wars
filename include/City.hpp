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

    void setExistingSpy(bool spy);

    bool getExistenceOfSpy();
    virtual int getCapacity() const = 0;
    virtual ~City() = default;
 
protected:
    std::pair<int, int> coordinates;
    bool spyExistence;
};
#endif
