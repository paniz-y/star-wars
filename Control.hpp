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
#include <random>
#include <float.h>
#include "Spaceship.hpp"
#include "City.hpp"
#include "BaseCity.hpp"
#include "CivilCity.hpp"
#include "Data.hpp"
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
    void initializeMap();
    std::vector<std::shared_ptr<City>> initializeAllBaseCitiesInAllScenarioa();
    std::vector<std::shared_ptr<City>> readCivilCitysFromFile();
    std::vector<std::shared_ptr<City>> readEnemyCitysFromFile();
    std::shared_ptr<Spaceship> findSuitableSpaceshipForBaseCities(std::string spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile);
    std::vector<std::shared_ptr<City>> initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense);
    void initializePriceFile();
    std::vector<std::pair<std::string, int>> readPricesFromFile();
    void initializeSpaceshipsWithPrices(std::vector<std::pair<std::string, int>> spaceships);
    std::vector<std::pair<int, int>> updateSpiesAfterEachNight();
    std::vector<std::pair<int, int>> generatingRandomSpiesForEachNight(int spies);
    int initializeRandomNumberOfSpiesForEachNight();
    void updateDefenseRatioAfterEachNight();
    void updateSpiesAndDefenseRatiosForEachNight();
    void removeAllSpiesAfterEachNight();
    void updateSpiesCoordinatesAfterEachNight(std::vector<std::pair<int, int>> spies);
    std::vector<std::shared_ptr<City>> initializeBaseCitiesWithOutSpaceships(std::vector<std::pair<int, int>> coorrdinates, std::vector<int> spies);
    std::vector<std::shared_ptr<Spaceship>> initializeUnknownSpaceships(std::vector<std::string> spaceships);
    void setMapMaxSize(int size);
    void initializeAllSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships, std::pair<int, int> coordinates);
    void initializeListOfBaseAndCivilCities(std::vector<std::shared_ptr<City>> base, std::vector<std::shared_ptr<City>> civil);
    void collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities);
    void routing(AStar aStar);
    bool isSpaceshipRadarResistant(std::shared_ptr<Spaceship> spaceship, int numOfSpies);
    void controlDestructions(int des);
    void IdentifyPriorityEnemyTarget(AStar aStar);
    void setSpiesAtThePathForEachDesination(AStar aStar);
    static bool compareTwoRoutsBasedOnSpies(const PathResult &first, const PathResult &second);
    static bool compareTwoRoutsBasedOnDefenseRatio(const PathResult &first, const PathResult &second);
    static bool compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction(const std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> &first, const std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> &second);
    static bool compareSpaceshipsBasedOnDestructionInAscendingOrder(const std::shared_ptr<Spaceship> &first, const std::shared_ptr<Spaceship> &second);
    static bool compareSpaceshipsBasedOnDestructionInDescendingOrder(const std::shared_ptr<Spaceship> &first, const std::shared_ptr<Spaceship> &second);
    void findValidReachedDestinations(); // find paths that reach an enemy city
    void findPathForARadarResistantSpaceship();
    void findPathBasedOnTotalDistance(AStar aStar); // find paths that don't exceed total distance of the spaceship
    PathResult findBestDestinationBasedOnDefenseRatioForEachSpaceship(const std::shared_ptr<Spaceship> &spaceship);
    void findTheFarthestEnemyCity(std::vector<std::shared_ptr<City>> &enemy);
    static bool compareEnemiesBasedOnHorizontalDistance(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second);
    static bool compareEnemiesBasedOnVerticalDistance(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second);
    void updateCurrentDefenseRatio(const std::shared_ptr<City> &finalDEstinationForCurrentSpaceship);
    void findSpaceshipForSeventhScenario();
    void displayTheFinalResult(const std::vector<std::shared_ptr<City>> &finalRes, const std::shared_ptr<Spaceship> &spaceship);
    void setAStarResults(std::vector<PathResult> pathResults);
    void findPathBasedOnMaxLength(const std::shared_ptr<Spaceship> &spaceship);
    void routingForThirdScenario(AStar aStar);
    void routingForFifthScenario(AStar aStar);
    void routingForSixthScenario(AStar aStar);
    bool ifDestinationHasDefenseRatio(const std::shared_ptr<City> &destination);
    void sortSpaceshipsBasedOnDestructionInAscendingOrder(std::vector<std::shared_ptr<Spaceship>> &);
    void sortSpaceshipsBasedOnDestructionInDecendingOrder(std::vector<std::shared_ptr<Spaceship>>);
    void initializeNumOfReachedSpaceshipsToEachDestination();
    void incrementNumOfReachedSpaceshipsToEachDestination();
    void initializeTrackedCitiesForEachSpaceship(const std::shared_ptr<Spaceship> &spaceship, AStar aStar);
    void controlingNightsForFifthScenario();
    void clearAllAStarRelatedData();
    void initializeListOfBaseCities(const std::vector<std::shared_ptr<City>> &baseCities);
    void setAStarResultsForEachSpaceship(std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> existingPathsForEachSpaceship);
    void findValidReachedDestinationsForUnknownSpaceship();
    PathResult findBestDestinationBasedOnDefenseRatioForEachBaseCity(const std::shared_ptr<City> &baseCity);
    void initializeTrackedCitiesForEachBaseCity(const std::shared_ptr<City> &baseCity, AStar aStar);
    void separateBTypeAndCTypeSpaceships();
    std::shared_ptr<Spaceship> findSuitableSpaceshipForThisPath(const std::shared_ptr<Spaceship> &bType, const int &pathIdx);
    int findPathForThisSpaceship(const std::shared_ptr<Spaceship> &spaceship, std::shared_ptr<Spaceship> &bestChoiceSpaceshipForThisPath);
    void attributePathToSpaceship(const int &pathIdx, const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<Spaceship> &selectedSpaceshipForThisPath, AStar aStar);
    void displayMissedSpaceshipFromThisBase(const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<City> &base);
    bool canSpaceshipReachDestinationFromThisBase(const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<City> &base, AStar aStar);

private:
    int amountOfDestruction;
    std::fstream mapFile;
    std::fstream priceFile;
    Map mapWithSpies;
    Data dataFile;
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
    std::vector<std::shared_ptr<EnemyCity>> listOfEnemyCities;
    std::unordered_map<std::shared_ptr<Spaceship>, int> spaceshipPrices;
    std::vector<std::shared_ptr<City>> enemiesAsCity;
    std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> AStarPathsForEachSpaceship;
    std::vector<std::shared_ptr<City>> listOfBaseAndCivilCities;
    std::unordered_map<std::pair<int, int>, std::shared_ptr<City>, HashForPair> coordsToCityPtr;
    std::vector<std::shared_ptr<City>> allCities;
    std::vector<PathResult> AStarResults;
    std::unordered_map<std::shared_ptr<City>, int> numOfReachedSpaceshipsToEachDestination;
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, int>> numOfSpiesForEachDestinationOfEachSpaceship;
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>>> trackedCitiesForEachSpaceship;
    std::unordered_map<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> ReachedSpaceshipsToEachDestination;
    // std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, int>> numOfSpiesForEachDestinationOfEachSpaceship;
    std::vector<std::shared_ptr<City>> listOfBaseCities;
    std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>> AStarPathsForEachBaseCity;
    std::unordered_map<std::shared_ptr<City>, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>>> trackedCitiesForEachBaseCity;
    std::vector<std::shared_ptr<Spaceship>> listOfBTypeSpaceships;
    std::vector<std::shared_ptr<Spaceship>> listOfCTypeSpaceships;
};
#endif