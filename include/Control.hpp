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
        return h1 ^ (h2 << 1);
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
    std::shared_ptr<Spaceship> findSuitableSpaceshipForBaseCities(const std::string &spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeBaseCities(const std::vector<std::pair<int, int>> &baseCityCoodinatesFromFile, const std::vector<int> &baseCitySpyFromFile, const std::vector<std::pair<int, std::vector<std::string>>> &spaceshipsInBaseCities);
    std::vector<std::shared_ptr<City>> initializeCivilCities(const std::vector<std::pair<int, int>> &civilCityCoodinatesFromFile, const std::vector<int> &civilCitySpyFromFile);
    std::vector<std::shared_ptr<City>> initializeEnemyCities(const std::vector<std::pair<int, int>> &enemyCityCoodinatesFromFile, const std::vector<int> &enemyCitySpyFromFile, const std::vector<Defense> &enemyCitiesDefense);
    void initializePriceFile();
    std::vector<std::pair<std::string, int>> readPricesFromFile();
    void initializeSpaceshipsWithPrices(std::vector<std::pair<std::string, int>> spaceships);
    std::vector<std::pair<int, int>> updateSpiesAfterEachNight();
    std::vector<std::pair<int, int>> generatingRandomSpiesForEachNight(const int &spies);
    int initializeRandomNumberOfSpiesForEachNight();
    void updateDefenseRatioAfterEachNight();
    void updateSpiesAndDefenseRatiosForEachNight();
    void removeAllSpiesAfterEachNight();
    void updateSpiesCoordinatesAfterEachNight(const std::vector<std::pair<int, int>> &spies);
    std::vector<std::shared_ptr<City>> initializeBaseCitiesWithoutSpaceships(const std::vector<std::pair<int, int>> &coorrdinates, const std::vector<int> &spies);
    std::vector<std::shared_ptr<Spaceship>> initializeUnknownSpaceships(const std::vector<std::string> &spaceships);
    void setMapMaxSize(const int &size);
    void initializeAllSpaceships(const std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::pair<int, int> &coordinates);
    void collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities);
    bool isSpaceshipRadarResistant(const std::shared_ptr<Spaceship> &spaceship, const int &numOfSpies);
    void controlDestructions(const int &des);
    void IdentifyPriorityEnemyTarget(AStar aStar);
    void setSpiesAtThePathForEachDesination(AStar aStar);
    static bool compareTwoRoutsBasedOnSpies(const PathResult &first, const PathResult &second);
    static bool compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction(const std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> &first, const std::pair<std::shared_ptr<City>, const std::vector<std::shared_ptr<Spaceship>>> &second);
    static bool compareSpaceshipsBasedOnDestructionInAscendingOrder(const std::shared_ptr<Spaceship> &first, const std::shared_ptr<Spaceship> &second);
    void findValidReachedDestinations(); // find paths that reach an enemy city
    void findPathForARadarResistantSpaceship();
    void findPathBasedOnTotalDistance(AStar aStar); // find paths that don't exceed total distance of the spaceship
    void findTheFarthestEnemyCity(std::vector<std::shared_ptr<City>> &enemy);
    static bool compareEnemiesBasedOnVerticalDistance(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second);
    void updateCurrentDefenseRatio(const std::shared_ptr<City> &finalDEstinationForCurrentSpaceship);
    void findSpaceshipForSeventhScenario();
    void displayTheFinalResult(const std::vector<std::shared_ptr<City>> &finalRes, const std::shared_ptr<Spaceship> &spaceship);
    void setAStarResults(const std::vector<PathResult> &pathResults);
    void routingForThirdScenario(AStar aStar);

    void routing(AStar aStar);
    bool ifDestinationHasDefenseRatio(const std::shared_ptr<City> &destination);
    void sortSpaceshipsBasedOnDestructionInAscendingOrder(std::vector<std::shared_ptr<Spaceship>> &spaceships);
    void incrementReachedSpaceshipsToEachDestination();
    void initializeTrackedCitiesForEachSpaceship(const std::shared_ptr<Spaceship> &spaceship, AStar aStar);
    void controlingNightsForFifthScenario();
    void clearAllAStarRelatedData();
    void initializeListOfBaseCities(const std::vector<std::shared_ptr<City>> &baseCities);
    void setAStarResultsForEachSpaceship(const std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> &existingPathsForEachSpaceship);
    std::shared_ptr<Spaceship> findSuitableSpaceshipForThisPath(const std::shared_ptr<Spaceship> &spaceship, const int &pathIdx);
    int findPathForThisSpaceship(const std::shared_ptr<Spaceship> &spaceship, std::shared_ptr<Spaceship> &bestChoiceSpaceshipForThisPath);
    void attributePathToSpaceship(const int &pathIdx, const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<Spaceship> &selectedSpaceshipForThisPath, AStar aStar, const std::shared_ptr<City> &base);
    void displayMissedSpaceshipFromThisBase(const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<City> &base);
    bool canSpaceshipReachDestinationFromThisBase(const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<City> &base, AStar aStar);
    bool isFifthScenario();
    bool isThirdScenario();
    void hasReachedDestinationWithNoDefenseRatio(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, const std::shared_ptr<City> &des, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached);
    void hasReachedDestinationWithDefenseRatio(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, const std::shared_ptr<City> &des, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached);
    void reachedWhileBeingRadarResistant(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached);
    void reachedWhileNotBeingRadarResistant(std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship);
    void findDestinationDefenseRatioStatus(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &des, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached);
    void findSpaceshipHasReachedStatus(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &des, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached);

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
    std::vector<std::shared_ptr<Spaceship>> listOfSpaceships;
    std::vector<std::shared_ptr<City>> listOfAllCities;
    std::vector<std::shared_ptr<EnemyCity>> listOfEnemyCities;
    std::vector<std::shared_ptr<City>> listOfBaseCities;
    std::unordered_map<std::shared_ptr<Spaceship>, int> spaceshipPrices;
    std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> AStarPathsForEachSpaceship;
    std::unordered_map<std::pair<int, int>, std::shared_ptr<City>, HashForPair> coordsToCityPtr;
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, int>> numOfSpiesForEachDestinationOfEachSpaceship;
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>>> trackedCitiesForEachSpaceship;
    std::unordered_map<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> reachedSpaceshipsToEachDestination;
    std::vector<PathResult> AStarResults;
};
#endif