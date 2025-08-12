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
#include <algorithm>
#include <sstream>
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
#include "AStar.hpp"

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
struct SharedPtrPairHash
{
    template <typename T, typename U>
    size_t operator()(const std::pair<std::shared_ptr<T>, std::shared_ptr<U>> &p) const
    {
        return std::hash<void *>{}(p.first.get()) ^ (std::hash<void *>{}(p.second.get()) << 1);
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
    std::shared_ptr<Spaceship> findSuitableSpaceshipForBaseCities(std::string spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile);
    std::vector<std::shared_ptr<City>> initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense);
    void readMaxMapSizeFromFile();
    std::vector<std::string> readUnknownSpaceshipesFromFile();
    std::vector<int> readBaseCpacitesFromFile();
    std::vector<std::pair<int, int>> readBaseCorrdinatesFromFile();
    std::vector<int> readSpiesOfBasesFromFile();
    void readScenarioNumberFromFile();
    std::vector<std::shared_ptr<City>> initializeBaseCitiesWithOutSpaceships(std::vector<std::pair<int, int>> coorrdinates, std::vector<int> spies);
    std::vector<std::shared_ptr<Spaceship>> initializeUnknownSpaceships(std::vector<std::string> spaceships);
    void readNumberOfBasesFromFile();
    std::vector<std::pair<int, std::vector<std::string>>> readSpaceshipsOfBasesFromFile();
    void initializeAllSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships, std::pair<int, int> coordinates);
    void initializeListOfBaseAndCivilCities(std::vector<std::shared_ptr<City>> base, std::vector<std::shared_ptr<City>> civil);
    void collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities);
    void routing();
    bool isSpaceshipRadarResistant(std::shared_ptr<Spaceship> spaceship, int numOfSpies);
    void controlDestructions(int des);
    static bool compareTwoRoutsBasedOnSpies(const PathResult &first, const PathResult &second);
    static bool compareTwoRoutsBasedOnDefenseRatio(const PathResult &first, const PathResult &second);
    void findValidReachedDestinations();
    void findPathForARadarResistantSpaceship(const std::shared_ptr<Spaceship> &spaceship);
    void findPathBasedOnTotalDistance(const std::shared_ptr<Spaceship> &spaceship);
    PathResult findBestDestinationBasedOnDefenseRatio();
    void findTheFarthestEnemyCity(std::vector<std::shared_ptr<City>> &enemy);
    static bool compareEnemiesBasedOnDistance(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second);
    void updateCurrentDefenseRatio(const PathResult &finalResultForCurrentSpaceship);
    void displayTheFinalResult(std::vector<std::shared_ptr<City>> finalRes);
    void setAStarResults(std::vector<PathResult> pathResults);
    void findPathBasedOnMaxLength(const std::shared_ptr<Spaceship> &spaceship);
    void routingForThirdScenario();

private:
    int scenario;
    int numOfCitys;
    int numOfBaseCities;
    int numOfCivilCitys;
    int numOfEnemyCitys;
    int amountOfDestruction;
    std::fstream mapFile;
    Map mapWithSpies;
    Map mapWithDefenses;
    AStar aStar;
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
    std::vector<std::shared_ptr<City>> allCities;
    std::vector<PathResult> AStarResults;
    std::unordered_map<std::shared_ptr<City>, int> numOfReachedSpaceshipsToEachCity;
};
#endif