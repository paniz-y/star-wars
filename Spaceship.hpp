#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include <string>
class Spaceship
{
public:
    Spaceship(int dis , int radar , int distruct , int controlDistance ,std::string type);
    void destroy();
    void setDistance(int dis);
    void setRadarResistency(int radar);
    void setDistruction(int distruct);
    void setControlLessDictance(int controlDictance);
    void setTypeOfSpaceship(std::string type);
    
    int getDistance();
    int setRadarResistency();
    int setDistruction();
    int setControlLessDictance();
    std::string setTypeOfSpaceship();


protected:
    int distance;
    int radarResistency;
    int distruction;
    int controlLessDictance;
    std ::string TypeOfSpaceship;
};
#endif