#ifndef BASECITY_HPP
#define BASECITY_HPP
#include <vector>
#include "City.hpp"
#include "Spaceship.hpp"

class BaseCity : public City
{
public:
    BaseCity(std::pair<int, int> coords, bool spy, std::vector<std::shared_ptr<Spaceship>> spaceships);
    BaseCity(std::pair<int, int> coords, bool spy);
    void setListOfSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships);
    std::vector<std::shared_ptr<Spaceship>> getListOfSpaceships();
    int getCapacity() const;
    void setCapacity(int capacity);

private:
    std ::vector<std::shared_ptr<Spaceship>> listOfSpaceships;
    int baseCapacity;
};

#endif