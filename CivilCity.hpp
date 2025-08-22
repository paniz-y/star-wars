#ifndef CIVILCITY_HPP
#define CIVILCITY_HPP
#include "City.hpp"
#include "Spaceship.hpp"
#include <vector>
class CivilCity : public City
{
public:
CivilCity(std::pair<int , int> , bool);
int getCapacity() const override;
private:

    
    
};

#endif