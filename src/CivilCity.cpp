#include "CivilCity.hpp"

CivilCity::CivilCity(std::pair<int , int> coord , bool spy) : City (coord , spy){}

int CivilCity::getCapacity() const
{
    return 0;//to avoid the class become pure virtual
}

CivilCity::~CivilCity()
{}
