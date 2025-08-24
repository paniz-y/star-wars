#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include <string>
#include <utility>
class Spaceship
{
public:
    Spaceship(int dis, int radar, int distruct, int controlDistance, std::string type);
    void destroy();
    void setDistance(int dis);
    void setRadarResistance(int radar);
    void setDestruction(int distruct);
    void setUncontrolledDistance(int controlDictance);
    void setTypeOfSpaceship(std::string type);
    void setCoordinates(std::pair<int, int> coords);
    std::pair<int, int> getCoordinates();
    int getDistance();
    int getRadarResistance();
    int getDestruction();
    int getUncontrolledDistance();
    std::string getTypeOfSpaceship();
    std::string getNameOfSpaceship();
    void setName(std::string name);
    int detected();
    bool isStillResistant();
    virtual ~Spaceship();
    void setHasReachedDestination(const bool &reached);
    bool getHasReachedDestination();

protected:
    int distance;
    int radarResistance;
    int destruction;
    int uncontrolledDistance;
    std::string nameOfSpaceship;
    std ::string typeOfSpaceship;
    std::pair<int, int> coordinats;
    bool hasReachedDestination = false;
};
#endif