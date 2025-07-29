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
// #include <tuple>
#include <float.h>
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
struct HashForPair
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the two hashes
    }
};

class Control
{

public:
    Control();
    void readMapFromFile();
    std::vector<std::shared_ptr<City>> readBaseCitysFromFile();
    std::vector<std::shared_ptr<City>> readCivilCitysFromFile();
    std::vector<std::shared_ptr<City>> readEnemyCitysFromFile();
    std::vector<std::shared_ptr<Spaceship>> findSuitableSpaceshipForBaseCities(std::vector<std::pair<int, std::string>> spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::string>> spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile);
    std::vector<std::shared_ptr<City>> initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense);
    void readMaxMapSizeFromFile();
    void initializeCorrespondentCityForEachSpaceship();
    void initializeAllSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships, std::pair<int, int> coordinates);
    std::pair<int, int> AStarRoutingForSpys(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship); // uses A* search algorithm for routing
    int AStarRoutingForDefenses(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship);             // uses A* search algorithm for routing
    void initializeListOfBaseAndCivilCities(std::vector<std::shared_ptr<City>> base, std::vector<std::shared_ptr<City>> civil);
    std::vector<std::shared_ptr<City>> collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities);
    void routing();
    bool isSpaceshipRadarResistant(int spaceshipRadarResistance);
    void controlDestructions(int des);
    int decreaseRadarResistant(std::shared_ptr<City> city, int spaceshipRadarResistance);
    // void routing2();

    int amountOfDestruction;
private:
    int scenario;
    int numOfCitys;
    int numOfBaseCitys;
    int numOfCivilCitys;
    int numOfEnemyCitys;
    std::fstream mapFile;
    Map mapWithSpys;
    Map mapWithDefenses;
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
    std::vector<std::shared_ptr<Spaceship>> allSpaceships;
    std::vector<EnemyCity> listOfEnemyCities;
    std::vector<std::shared_ptr<City>> listOfBaseAndCivilCities;
    std::unordered_map<std::pair<int, int>, std::shared_ptr<City>, HashForPair> coordsToCityPtr;
    std::vector<std::pair<std::shared_ptr<Spaceship>, std::shared_ptr<City>>> correspondentCityForEachSpaceship;
    std::vector<std::pair<int, int>> routingResultsForSpys;
    std::vector<int> routingResultsForDefense;
    std::shared_ptr<City> previouseVisitedCity;
    // std::vector<std::pair<int, int>> baseCityCoodinates;
    // std::vector<std::pair<int, int>> civilCityCoodinates;
    // std::vector<std::pair<int, int>> enemyCityCoodinates;

    // std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> map;
};
#endif