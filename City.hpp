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
    virtual bool getHasDefense() const;
    virtual void setDefense(bool);
    virtual int getCapacity() const = 0;
 
protected:
    std::pair<int, int> coordinates;
    bool spyExistence;
    bool hasDefense;
};
#endif
