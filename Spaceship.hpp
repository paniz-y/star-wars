#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include <string>
#include <utility>
class Spaceship
{
public:
    Spaceship(int dis , int radar , int distruct , int controlDistance ,std::string type);
    void destroy();
    void setDistance(int dis);
    void setRadarResistance(int radar);
    void setDestruction(int distruct);
    void setControlLessDictance(int controlDictance);
    void setTypeOfSpaceship(std::string type);
    void setCoordinates(std::pair<int, int> coords);
    std::pair<int, int> getCoordinates();
    int getDistance();
    int getRadarResistance();
    int getDestruction();
    int setControlLessDictance();
    std::string getTypeOfSpaceship();
    int getControlLessDictance();
    std::string getNameOfSpaceship();
    void setName(std::string name);
    int detected();
    bool isStillResistant();

protected:
    int distance;
    int radarResistance;
    int Destruction;
    int controlLessDictance;
    std::string nameOfSpaceship;
    std ::string TypeOfSpaceship;
    std::pair<int, int> coordinats;
};
#endif