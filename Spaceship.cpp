#include "Spaceship.hpp"

Spaceship::Spaceship(int dis, int radar, int distruct, int controlDictance, std::string type)
{
    setDistance(dis);
    setRadarResistance(radar);
    setDistruction(distruct);
    setControlLessDictance(controlDictance);
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
void Spaceship::setDistruction(int distruct)
{
    this->distruction = distruct;
}

void Spaceship::setControlLessDictance(int controlDictance)
{
    this->controlLessDictance = controlDictance;
}
void Spaceship::setTypeOfSpaceship(std::string type)
{
    this->TypeOfSpaceship = type;
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
int Spaceship::setDistruction()
{
    return distruction;
}
int Spaceship::setControlLessDictance()
{
    return controlLessDictance;
}
std::string Spaceship::getTypeOfSpaceship()
{
    return TypeOfSpaceship;
}

int Spaceship::getControlLessDictance()
{
    return controlLessDictance;
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
