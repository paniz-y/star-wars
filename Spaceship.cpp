#include "Spaceship.hpp"

Spaceship::Spaceship(int dis, int radar, int distruct, int controlDictance, std::string type)
{
    setDistance(dis);
    setRadarResistance(radar);
    setDestruction(distruct);
    setUncontrolledDistance(controlDictance);
    setTypeOfSpaceship(type);
}

void Spaceship::setDistance(int dis)
{
    this->distance = dis;
}
void Spaceship::setRadarResistance(int radar)
{
    this->radarResistance = radar;
}
void Spaceship::setDestruction(int distruct)
{
    this->destruction = distruct;
}

void Spaceship::setUncontrolledDistance(int controlDictance)
{
    this->uncontrolledDistance = controlDictance;
}
void Spaceship::setTypeOfSpaceship(std::string type)
{
    this->typeOfSpaceship = type;
}

void Spaceship::setCoordinates(std::pair<int, int> coords)
{
    coordinats = coords;
}
std::pair<int, int> Spaceship::getCoordinates()
{
    return coordinats;
}
int Spaceship::getDistance()
{
    return distance;
}
int Spaceship::getRadarResistance()
{
    return radarResistance;
}
int Spaceship::getDestruction()
{
    return destruction;
}
int Spaceship::getUncontrolledDistance()
{
    return uncontrolledDistance;
}
std::string Spaceship::getTypeOfSpaceship()
{
    return typeOfSpaceship;
}

std::string Spaceship::getNameOfSpaceship()
{
    return nameOfSpaceship;
}

void Spaceship::setName(std::string name)
{
    nameOfSpaceship = name;
}

int Spaceship::detected()
{
    if (radarResistance > 0)
        radarResistance--;
    return radarResistance;
}

bool Spaceship::isStillResistant()
{
    if (radarResistance > 0)
    {
        return true;
    }
    return false;
}

Spaceship::~Spaceship() = default;