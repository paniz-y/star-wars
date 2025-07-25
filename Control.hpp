#ifndef CONTROL_HPP
#define CONTROL_HPP
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "Spaceship.hpp"
#include "City.hpp"
#include "BaseCity.hpp"
#include "CivilCity.hpp"
#include "Map.hpp"
#include "EnemyCity.hpp"
#include "Defense.hpp"
#include "XwingStarFighter.hpp"
#include "DeathStar.hpp"
#include "TieFighter.hpp"
#include "RazorCrest.hpp"
#include "StarDestroyer.hpp"
#include "Mantis.hpp"
#include "MillenniumFalcon.hpp"
#include "DeathStar.hpp"
#include "Awing.hpp"
struct Node
{
    std::shared_ptr<City> currCity;
    std::shared_ptr<City> prevCity;
    double g;
    double heuristic;
    double calculateF() const
    {
        return g + heuristic;
    }
    bool operator>(const Node &node) const
    {
        return calculateF() > node.calculateF();
    }
};
class Control
{

public:
    void readMapFromFile();
    void readBaseCitysFromFile();
    void readCivilCitysFromFile();
    void readEnemyCitysFromFile();
    std::vector<std::shared_ptr<Spaceship>> findSutableSpaceshipForBaseCities(std::vector<std::pair<int, std::string>> spaceshipsInBaseCities);
    std::vector <BaseCity> initializedBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::string>> spaceshipsInBaseCities);
    std::vector <CivilCity> initializedCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile);
    std::vector <EnemyCity> initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense);
    int CalculateDistance();
    void AStarRouting(Map map, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination); // uses A* search algorithm for routing

private:
    int scenario;
    int numOfCitys;
    int numOfBaseCitys;
    int numOfCivilCitys;
    int numOfEnemyCitys;
    std::fstream mapFile;
    Map map;
    enum class spaceshipType
    {
        Awing,
        DeathStar,
        Mantis,
        MillenniumFalcon,
        RazorCrest,
        StarDestroyer,
        TieFighter,
        XwingStarFighter,
        UNKNOWN
    };
    spaceshipType stringToSpaceshipType(const std::string &str)
    {
        if (str == "Awing")
            return spaceshipType::Awing;
        if (str == "DeathStar")
            return spaceshipType::DeathStar;
        if (str == "Mantis")
            return spaceshipType::Mantis;
        if (str == "MillenniumFalcon")
            return spaceshipType::MillenniumFalcon;
        if (str == "RazorCrest")
            return spaceshipType::RazorCrest;
        if (str == "StarDestroyer")
            return spaceshipType::StarDestroyer;
        if (str == "TieFighter")
            return spaceshipType::TieFighter;
        if (str == "XwingStarFighter")
            return spaceshipType::XwingStarFighter;
        return spaceshipType::UNKNOWN;
    }
    // std::vector<std::pair<int, int>> baseCityCoodinates;
    // std::vector<std::pair<int, int>> civilCityCoodinates;
    // std::vector<std::pair<int, int>> enemyCityCoodinates;

    // std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> map;
};
#endif