#include "Control.hpp"

Control::Control()
{
    amountOfDestruction = 0;
}

void Control::initializePriceFile()
{
    priceFile.open("price.txt", std::ios::in);
    if (!priceFile.is_open())
    {
        std::cerr << "Unable to the price open file" << std::endl;
        return;
    }
    std::vector<std::pair<std::string, int>> spaceshipPrices(8);
    spaceshipPrices = readPricesFromFile();
    initializeSpaceshipsWithPrices(spaceshipPrices);
    priceFile.close();
}
std::vector<std::pair<std::string, int>> Control::readPricesFromFile()
{
    std::string nameOfSpaceshipString, priceOfSpaceshipString;
    std::vector<std::pair<std::string, int>> spaceshipPrices(8);
    for (int i = 0; i < 8; i++)
    {
        priceFile >> nameOfSpaceshipString >> spaceshipPrices[i].first >> priceOfSpaceshipString >> spaceshipPrices[i].second;
    }
    return spaceshipPrices;
}
void Control::initializeSpaceshipsWithPrices(std::vector<std::pair<std::string, int>> spaceships)
{
    for (int i = 0; i < spaceships.size(); i++)
    {
        std::shared_ptr<Spaceship> setSpaceshipWithPrice = findSuitableSpaceshipForBaseCities(spaceships[i].first);
        spaceshipPrices[setSpaceshipWithPrice] = spaceships[i].second;
    }
}
std::vector<std::shared_ptr<City>> Control::initializeAllBaseCitiesInAllScenarioa()
{
    std::vector<std::shared_ptr<City>> baseCityForMap;

    if (dataFile.getScenario() == 7)
    {
        baseCityForMap = initializeBaseCitiesWithoutSpaceships(dataFile.getBaseCityCoodinates(), dataFile.getBaseCitySpies());
    }
    else if (dataFile.getScenario() != 3)
    {
        baseCityForMap = initializeBaseCities(dataFile.getBaseCityCoodinates(), dataFile.getBaseCitySpies(), dataFile.getSpaceshipsInBaseCities());
    }
    else
    {
        listOfSpaceships = initializeUnknownSpaceships(dataFile.getSpaceshipsToBeDivided());
        baseCityForMap = initializeBaseCitiesWithoutSpaceships(dataFile.getBaseCityCoodinates(), dataFile.getBaseCitySpies());
    }
    return baseCityForMap;
}
void Control::setMapMaxSize(const int &maxMapSize)
{
    mapWithSpies.setMaxSize(maxMapSize);
}
std::shared_ptr<Spaceship> Control::findSuitableSpaceshipForBaseCities(const std::string &spaceshipsInBaseCities)
{
    spaceshipType type = stringToSpaceshipType(spaceshipsInBaseCities);
    switch (type)
    {
    case spaceshipType::Awing:
    {
        return std::make_shared<Awing>();
    }
    case spaceshipType::DeathStar:
    {
        return std::make_shared<DeathStar>();
    }
    case spaceshipType::Mantis:
    {
        return std::make_shared<Mantis>();
    }

    case spaceshipType::MillenniumFalcon:
    {
        return std::make_shared<MillenniumFalcon>();
    }

    case spaceshipType::RazorCrest:
    {
        return std::make_shared<RazorCrest>();
    }

    case spaceshipType::StarDestroyer:
    {
        return std::make_shared<StarDestroyer>();
    }

    case spaceshipType::TieFighter:
    {
        return std::make_shared<TieFighter>();
    }

    case spaceshipType::XwingStarFighter:
    {
        return std::make_shared<XwingStarFighter>();
    }

    default:
        throw std::invalid_argument("Unknown city type: " + spaceshipsInBaseCities);
    }
}
std::vector<std::shared_ptr<City>> Control::readCivilCitysFromFile()
{
    std::vector<std::shared_ptr<City>> civilCitiesForTheMap = initializeCivilCities(dataFile.getCivilCityCoodinates(), dataFile.getCivilCitySpies());
    return civilCitiesForTheMap;
}
std::vector<std::shared_ptr<City>> Control::readEnemyCitysFromFile()
{
    std::vector<std::shared_ptr<City>> enemyCitiesMadeForMap = initializeEnemyCities(dataFile.getEnemyCityCoordinates(), dataFile.getEnemyCitySpies(), dataFile.getEnemyCitiesDefense());

    return enemyCitiesMadeForMap;
}

void Control::findTheFarthestEnemyCity(std::vector<std::shared_ptr<City>> &enemies)
{
    std::sort(enemies.begin(), enemies.end(), compareEnemiesBasedOnVerticalDistance);
}

bool Control::compareEnemiesBasedOnVerticalDistance(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second)
{
    if (std::shared_ptr<EnemyCity> firstEnemy = std::dynamic_pointer_cast<EnemyCity>(first))
    {
        if (std::shared_ptr<EnemyCity> secondEnemy = std::dynamic_pointer_cast<EnemyCity>(second))
        {
            return firstEnemy->getCoordinates().second < secondEnemy->getCoordinates().second;
        }
    }
    return false;
}
void Control::updateCurrentDefenseRatio(const std::shared_ptr<City> &finalDestinationForCurrentSpaceship)
{
    if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(finalDestinationForCurrentSpaceship))
    {
        if (enemy->getDefense().getRatio() > 0)
        {
            enemy->defenseForChange().defend();
        }
    }
}
void Control::findSpaceshipForSeventhScenario()
{
    // std::vector<std::vector<int>> dpForSpaceships(spaceshipPrices.size() + 1, std::vector<int>(maxDamage + 1, 0)); // initialize dp table
    // std::vector<std::pair<std::shared_ptr<Spaceship>, int>> spaceshipsWithPrices(spaceshipPrices.begin(), spaceshipPrices.end());

    // for (int i = 1; i <= spaceshipsWithPrices.size(); i++)
    // {
    //     for (int w = 0; w <= maxDamage; w++)
    //     {
    //         if (spaceshipsWithPrices[i - 1].second <= w) // determine whether the spaceship is affordable
    //         {
    //             dpForSpaceships[i][w] = std::max(dpForSpaceships[i - 1][w],                                                                                               // not taking the spaceship
    //                                              spaceshipsWithPrices[i - 1].first->getDestruction() + (dpForSpaceships[i - 1][w - spaceshipsWithPrices[i - 1].second])); // taking the spaceship
    //         }
    //         else
    //             dpForSpaceships[i][w] = dpForSpaceships[i - 1][w]; // the price is not affordable
    //     }
    // }
}
std::vector<std::shared_ptr<City>> Control::initializeEnemyCities(const std::vector<std::pair<int, int>> &enemyCityCoordinatesFromFile, const std::vector<int> &enemyCitySpyFromFile, const std::vector<Defense> &enemyCitiesDefense)
{
    std::vector<std::shared_ptr<City>> enemyCities;
    for (int i = 0; i < enemyCityCoordinatesFromFile.size(); i++)
    {
        std::shared_ptr<EnemyCity> enemyCityTmp = std::make_shared<EnemyCity>(enemyCityCoordinatesFromFile[i], enemyCitySpyFromFile[i], enemyCitiesDefense[i], true);
        listOfEnemyCities.emplace_back(enemyCityTmp);
        std::shared_ptr<EnemyCity> enemyPtrTmp = std::make_shared<EnemyCity>(enemyCityCoordinatesFromFile[i], enemyCitySpyFromFile[i], enemyCitiesDefense[i], true);
        enemyCities.emplace_back(enemyPtrTmp);
        coordsToCityPtr[enemyCityCoordinatesFromFile[i]] = enemyCities.back();
    }
    findTheFarthestEnemyCity(enemyCities);

    return enemyCities;
}
std::vector<std::shared_ptr<Spaceship>> Control::initializeUnknownSpaceships(const std::vector<std::string> &spaceships)
{
    std::vector<std::shared_ptr<Spaceship>> unknownSpaceships;

    for (int i = 0; i < spaceships.size(); i++)
    {
        unknownSpaceships.emplace_back(findSuitableSpaceshipForBaseCities(spaceships[i]));
    }
    return unknownSpaceships;
}
std::vector<std::shared_ptr<City>> Control::initializeBaseCities(const std::vector<std::pair<int, int>> &baseCityCoodinatesFromFile, const std::vector<int> &baseCitySpyFromFile, const std::vector<std::pair<int, std::vector<std::string>>> &spaceshipsInBaseCities)
{
    std::vector<std::shared_ptr<City>> baseCities;
    for (int i = 0; i < baseCityCoodinatesFromFile.size(); i++)
    {
        std::vector<std::shared_ptr<Spaceship>> spaceshipsFoundFromBaseCities;
        for (int k = 0; k < spaceshipsInBaseCities[i].second.size(); k++)
            spaceshipsFoundFromBaseCities.emplace_back(findSuitableSpaceshipForBaseCities(spaceshipsInBaseCities[i].second[k]));

        std::shared_ptr<BaseCity> basePtrTmp = std::make_shared<BaseCity>(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i], spaceshipsFoundFromBaseCities);

        initializeAllSpaceships(spaceshipsFoundFromBaseCities, baseCityCoodinatesFromFile[i]);
        baseCities.emplace_back(basePtrTmp);
        coordsToCityPtr[baseCityCoodinatesFromFile[i]] = baseCities.back();
    }
    return baseCities;
}
std::vector<std::shared_ptr<City>> Control::initializeBaseCitiesWithoutSpaceships(const std::vector<std::pair<int, int>> &baseCityCoodinatesFromFile, const std::vector<int> &baseCitySpyFromFile)
{
    std::vector<std::shared_ptr<City>> baseCities;
    for (int i = 0; i < baseCityCoodinatesFromFile.size(); i++)
    {
        std::shared_ptr<BaseCity> basePtrTmp = std::make_shared<BaseCity>(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i]);
        baseCities.emplace_back(basePtrTmp);
        coordsToCityPtr[baseCityCoodinatesFromFile[i]] = baseCities.back();
    }
    return baseCities;
}
std::vector<std::shared_ptr<City>> Control::initializeCivilCities(const std::vector<std::pair<int, int>> &civilCityCoodinatesFromFile, const std::vector<int> &civilCitySpyFromFile)
{
    std::vector<std::shared_ptr<City>> civilCities;
    for (int i = 0; i < civilCityCoodinatesFromFile.size(); i++)
    {
        std::shared_ptr<CivilCity> civilPtrTmp = std::make_shared<CivilCity>(civilCityCoodinatesFromFile[i], civilCitySpyFromFile[i]);
        civilCities.emplace_back(civilPtrTmp);
        coordsToCityPtr[civilCityCoodinatesFromFile[i]] = civilCities.back();
    }
    return civilCities;
}
void Control::initializeMap()
{
    dataFile.readMapFromFile();

    std::vector<std::shared_ptr<City>> baseCities = initializeAllBaseCitiesInAllScenarioa();
    std::vector<std::shared_ptr<City>> civilCities = readCivilCitysFromFile();
    std::vector<std::shared_ptr<City>> enemyCities = readEnemyCitysFromFile();

    setMapMaxSize(dataFile.getMaxMapSize());

    initializeListOfBaseCities(baseCities);

    collectAllCities(baseCities, civilCities, enemyCities);
    mapWithSpies.graphMap(listOfAllCities);
}

void Control::initializeAllSpaceships(const std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::pair<int, int> &coordinates)
{
    int listOfSpaceshipsSize = listOfSpaceships.size();

    for (int i{}; i < spaceships.size(); i++)
    {
        listOfSpaceships.emplace_back(spaceships[i]);
    }
    for (int i{}; i < spaceships.size(); i++)
    {
        listOfSpaceships[listOfSpaceshipsSize + i]->setCoordinates(coordinates);
    }
}

void Control::initializeListOfBaseCities(const std::vector<std::shared_ptr<City>> &baseCities)
{
    listOfBaseCities.insert(listOfBaseCities.end(), baseCities.begin(), baseCities.end());
}
std::shared_ptr<Spaceship> Control::findSuitableSpaceshipForThisPath(const std::shared_ptr<Spaceship> &spaceship, const int &pathIdx)
{
    if (AStarPathsForEachSpaceship[spaceship].size() != 0)
    {
        if (isSpaceshipRadarResistant(spaceship, AStarPathsForEachSpaceship[spaceship].at(pathIdx).numOfSpies))
        {
            return spaceship;
        }
        else
        {
            updateCurrentDefenseRatio(AStarPathsForEachSpaceship[spaceship].at(pathIdx).destination);
        }
    }
    return nullptr; // there is no valid path for this spaceship
}
int Control::findPathForThisSpaceship(const std::shared_ptr<Spaceship> &spaceship, std::shared_ptr<Spaceship> &bestChoiceSpaceshipForThisPath)
{

    for (int i{}; i < AStarPathsForEachSpaceship[spaceship].size(); i++)
    {
        bestChoiceSpaceshipForThisPath = findSuitableSpaceshipForThisPath(spaceship, i);
        if (bestChoiceSpaceshipForThisPath)
        {
            return i;
        }
    }
    return -1; // for this spaceship there is no valid path starting from this base
}

bool Control::canSpaceshipReachDestinationFromThisBase(const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<City> &base, AStar aStar)
{
    std::shared_ptr<Spaceship> selectedSpaceshipForThisPath;

    int pathFoundIdx = findPathForThisSpaceship(spaceship, selectedSpaceshipForThisPath);

    if (pathFoundIdx != -1) // this path is valid for this spaceship
    {
        attributePathToSpaceship(pathFoundIdx, spaceship, selectedSpaceshipForThisPath, aStar, base);
        return true;
    }
    displayMissedSpaceshipFromThisBase(spaceship, base);
    return false;
}

void Control::displayMissedSpaceshipFromThisBase(const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<City> &base)
{
    std::cout << spaceship->getNameOfSpaceship() << " would have been missed starting from base placed at: "
              << "(" << base->getCoordinates().first << " , " << base->getCoordinates().second << ")" << std::endl;
}

void Control::attributePathToSpaceship(const int &pathFoundIdx, const std::shared_ptr<Spaceship> &spaceship, const std::shared_ptr<Spaceship> &selectedSpaceshipForThisPath, AStar aStar, const std::shared_ptr<City> &base)
{
    reachedSpaceshipsToEachDestination[AStarPathsForEachSpaceship[spaceship][pathFoundIdx].destination].emplace_back(selectedSpaceshipForThisPath);

    std::vector<std::shared_ptr<City>> finalpathResult = aStar.backtrackAStarPath(base, coordsToCityPtr[((AStarPathsForEachSpaceship[spaceship][pathFoundIdx].destination)->getCoordinates())], trackedCitiesForEachSpaceship[spaceship]);
    controlDestructions(spaceship->getDestruction());
    displayTheFinalResult(finalpathResult, spaceship);
}

void Control::setAStarResultsForEachSpaceship(const std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> &existingPathsForEachSpaceship)
{
    AStarPathsForEachSpaceship = existingPathsForEachSpaceship;
}
void Control::collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities)
{

    listOfAllCities.insert(listOfAllCities.end(), baseCities.begin(), baseCities.end());
    listOfAllCities.insert(listOfAllCities.end(), civilCities.begin(), civilCities.end());
    listOfAllCities.insert(listOfAllCities.end(), enemyCities.begin(), enemyCities.end());
}

bool Control::isSpaceshipRadarResistant(const std::shared_ptr<Spaceship> &spaceship, const int &numOfSpies)
{
    if (numOfSpies < spaceship->getRadarResistance())
        return true;
    return false;
}
void Control::controlDestructions(const int &des)
{
    amountOfDestruction += des;
}

void Control::findValidReachedDestinations()
{
    for (auto spaceshipIt = AStarPathsForEachSpaceship.begin(); spaceshipIt != AStarPathsForEachSpaceship.end();)
    {
        for (auto pathIt = (*spaceshipIt).second.begin(); pathIt != (*spaceshipIt).second.end();)
        {
            if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(pathIt->destination))
            {
                pathIt++;
            }
            else
            {
                pathIt = (*spaceshipIt).second.erase(pathIt); // remove the path not reaching the enemy city
            }
        }
        if ((*spaceshipIt).second.empty() && !isThirdScenario())
        {
            std::cout << (*spaceshipIt).first->getNameOfSpaceship() << " placed at " << "(" << (*spaceshipIt).first->getCoordinates().first << " , " << (*spaceshipIt).first->getCoordinates().second << ")" << " could not reach a destination." << std::endl;
            spaceshipIt = AStarPathsForEachSpaceship.erase(spaceshipIt); // remove the spaceship that has no path left
        }
        else
            spaceshipIt++;
    }
}

void Control::findPathForARadarResistantSpaceship()
{
    for (auto &spaceship : AStarPathsForEachSpaceship) // iterate over each spaceship's paths
    {
        std::sort(spaceship.second.begin(), spaceship.second.end(), compareTwoRoutsBasedOnSpies); // sorting based on radar resistance

        for (auto it = spaceship.second.begin(); it != spaceship.second.end();)
        {
            if (isSpaceshipRadarResistant(spaceship.first, it->numOfSpies))
            {
                it++;
            }
            else
            {
                it = spaceship.second.erase(it); // remove the paths exceeding the radar
            }
        }
    }
}

void Control::findPathBasedOnTotalDistance(AStar aStar)
{
    for (auto spaceshipIt = AStarPathsForEachSpaceship.begin(); spaceshipIt != AStarPathsForEachSpaceship.end();)
    {
        for (auto it = (*spaceshipIt).second.begin(); it != (*spaceshipIt).second.end();)
        {
            if (aStar.heuristic(coordsToCityPtr[(*spaceshipIt).first->getCoordinates()], it->destination) <= (*spaceshipIt).first->getDistance())
            {
                it++;
            }
            else
            {
                it = (*spaceshipIt).second.erase(it); // deleting the pathes that exceeded the total distance of this spaceship
            }
        }
        if ((*spaceshipIt).second.empty() && !isThirdScenario())
        {
            std::cout << (*spaceshipIt).first->getNameOfSpaceship() << " placed at " << "(" << (*spaceshipIt).first->getCoordinates().first << " , " << (*spaceshipIt).first->getCoordinates().second << ")" << " exceeded the total distance and could not reach a destination." << std::endl;
            spaceshipIt = AStarPathsForEachSpaceship.erase(spaceshipIt); // deleting the spaceship that has no path left
        }
        else
            spaceshipIt++;
    }
}

bool Control::compareTwoRoutsBasedOnSpies(const PathResult &first, const PathResult &second)
{
    return first.numOfSpies < second.numOfSpies;
}

bool Control::compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction(const std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> &first, const std::pair<std::shared_ptr<City>, const std::vector<std::shared_ptr<Spaceship>>> &second)
{
    if (std::shared_ptr<EnemyCity> firstEnemy = std::dynamic_pointer_cast<EnemyCity>(first.first))
    {
        if (std::shared_ptr<EnemyCity> secondEnemy = std::dynamic_pointer_cast<EnemyCity>(second.first))
        {
            int numOfReachedSpaceshipsFirst = first.second.size() - firstEnemy->getDefense().getRatio();
            int numOfReachedSpaceshipsSecond = second.second.size() - secondEnemy->getDefense().getRatio();
            return numOfReachedSpaceshipsFirst > numOfReachedSpaceshipsSecond;
        }
    }
    return false;
}

bool Control::compareSpaceshipsBasedOnDestructionInAscendingOrder(const std::shared_ptr<Spaceship> &first, const std::shared_ptr<Spaceship> &second)
{
    return first->getDestruction() < second->getDestruction();
}

void Control::routingForThirdScenario(AStar aStar)
{
    for (auto &spaceship : listOfSpaceships)
    {
        for (auto &base : listOfBaseCities)
        {
            aStar.AStarSearch(mapWithSpies, coordsToCityPtr[base->getCoordinates()], listOfAllCities[listOfAllCities.size() - 1], spaceship);
            setAStarResults(aStar.getPathResults()); // set the results collected by Astar
            setAStarResultsForEachSpaceship(aStar.getExistingPathsForEachSpaceship());

            initializeTrackedCitiesForEachSpaceship(spaceship, aStar);
            findValidReachedDestinations();
            findPathBasedOnTotalDistance(aStar);
            if (canSpaceshipReachDestinationFromThisBase(spaceship, base, aStar))
            {
                break;
            }
        }
    }
}

std::vector<std::pair<int, int>> Control::updateSpiesAfterEachNight()
{
    int randomNumberOfSpies = initializeRandomNumberOfSpiesForEachNight();

    std::vector<std::pair<int, int>> newSpiesCoordinates(randomNumberOfSpies);
    newSpiesCoordinates = generatingRandomSpiesForEachNight(randomNumberOfSpies);

    return newSpiesCoordinates;
}
int Control::initializeRandomNumberOfSpiesForEachNight()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, listOfAllCities.size()); // shrink the number generated by gen to a range that can be used for numberOfSpies

    std::shuffle(listOfAllCities.begin(), listOfAllCities.end(), gen);

    int randomNumberOfSpies = distrib(gen); // new random number of spies
    return randomNumberOfSpies;
}

std::vector<std::pair<int, int>> Control::generatingRandomSpiesForEachNight(const int &randomNumberOfSpies)
{
    std::vector<std::pair<int, int>> newSpiesCoordinates(randomNumberOfSpies);

    for (int i = 0; i < randomNumberOfSpies; i++)
        newSpiesCoordinates[i] = listOfAllCities[i]->getCoordinates();

    return newSpiesCoordinates;
}
void Control::updateSpiesCoordinatesAfterEachNight(const std::vector<std::pair<int, int>> &spies)
{
    for (int i = 0; i < spies.size(); i++)
    {
        if (spies[i] == listOfAllCities[i]->getCoordinates())
        {
            listOfAllCities[i]->setExistingSpy(true);
        }
    }
}
void Control::removeAllSpiesAfterEachNight()
{
    for (int i = 0; i < listOfAllCities.size(); i++)
    {
        listOfAllCities[i]->setExistingSpy(false);
    }
}
void Control::updateDefenseRatioAfterEachNight()
{
    for (auto &cities : listOfAllCities)
    {
        if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(cities))
        {
            for (int i = 0; i < listOfEnemyCities.size(); i++)
            {
                if (enemy->getCoordinates() == listOfEnemyCities[i]->getCoordinates())
                {
                    enemy->setDefenseForRatio(listOfEnemyCities[i]->getDefense().getRatio());
                    break;
                }
            }
        }
    }
}
void Control::updateSpiesAndDefenseRatiosForEachNight()
{
    removeAllSpiesAfterEachNight();
    std::vector<std::pair<int, int>> updatedSpies = updateSpiesAfterEachNight();
    updateSpiesCoordinatesAfterEachNight(updatedSpies);
    updateDefenseRatioAfterEachNight();
}

void Control::controlingNightsForFifthScenario()
{
    for (int i = 0; i < 5; i++)
    {
        std::cout << i + 1 << " : " << std::endl;
        AStar aStar;
        routing(aStar);
        clearAllAStarRelatedData();
        updateSpiesAndDefenseRatiosForEachNight();
    }
}
void Control::clearAllAStarRelatedData()
{
    AStarPathsForEachSpaceship.clear();
    AStarResults.clear();
    trackedCitiesForEachSpaceship.clear();
    reachedSpaceshipsToEachDestination.clear();
}
void Control::hasReachedDestinationWithNoDefenseRatio(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, const std::shared_ptr<City> &des, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached)
{
    std::vector<std::shared_ptr<City>> finalpathResult = aStar.backtrackAStarPath(coordsToCityPtr[spaceships.back()->getCoordinates()], finalDestinationForCurrentSpaceship, trackedCitiesForEachSpaceship[spaceships.back()]);
    controlDestructions(spaceships.back()->getDestruction());
    displayTheFinalResult(finalpathResult, spaceships.back()); // display the final path and destruction
    spaceships.back()->setHasReachedDestination(true);
    auto itrTmp = spaceshipIt;
    while (itrTmp != spaceships.end())
    {
        itrTmp++;
    }
    spaceships.erase(itrTmp);
    hasPreviouseSpaceshipReached = true;
}
void Control::hasReachedDestinationWithDefenseRatio(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, const std::shared_ptr<City> &des, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached)
{
    if (isSpaceshipRadarResistant((*spaceshipIt), numOfSpiesForEachDestinationOfEachSpaceship[(*spaceshipIt)][des]))
    {

        reachedWhileBeingRadarResistant(aStar, spaceshipIt, spaceships, finalDestinationForCurrentSpaceship, hasPreviouseSpaceshipReached);
        if (isFifthScenario() && hasPreviouseSpaceshipReached)
        {
            return;
        }
    }
    else
    {
        reachedWhileNotBeingRadarResistant(spaceshipIt, spaceships, finalDestinationForCurrentSpaceship);
        if (isFifthScenario() && hasPreviouseSpaceshipReached)
        {
            return;
        }
    }
}

void Control::reachedWhileBeingRadarResistant(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached)
{
    std::vector<std::shared_ptr<City>> finalpathResult = aStar.backtrackAStarPath(coordsToCityPtr[(*spaceshipIt)->getCoordinates()], finalDestinationForCurrentSpaceship, trackedCitiesForEachSpaceship[(*spaceshipIt)]);

    controlDestructions((*spaceshipIt)->getDestruction());

    displayTheFinalResult(finalpathResult, (*spaceshipIt)); // display the final path and destruction

    (*spaceshipIt)->setHasReachedDestination(true);

    spaceshipIt = spaceships.erase(spaceshipIt);
    hasPreviouseSpaceshipReached = true;
}
void Control::reachedWhileNotBeingRadarResistant(std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship)
{
    (*spaceshipIt)->setHasReachedDestination(true);
    std::cout << (*spaceshipIt)->getNameOfSpaceship() << " placed at " << "(" << (*spaceshipIt)->getCoordinates().first << " , " << (*spaceshipIt)->getCoordinates().second << ")" << " has been hit by a defense." << std::endl;

    updateCurrentDefenseRatio(finalDestinationForCurrentSpaceship);
    spaceshipIt = spaceships.erase(spaceshipIt);
}
void Control::findDestinationDefenseRatioStatus(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &des, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached)
{
    if (!ifDestinationHasDefenseRatio(des))
    {
        hasReachedDestinationWithNoDefenseRatio(aStar, spaceshipIt, des, spaceships, finalDestinationForCurrentSpaceship, hasPreviouseSpaceshipReached);
        if (isFifthScenario() && hasPreviouseSpaceshipReached)
        {
            return;
        }
    }
    else
    {
        hasReachedDestinationWithDefenseRatio(aStar, spaceshipIt, des, spaceships, finalDestinationForCurrentSpaceship, hasPreviouseSpaceshipReached);
        if (isFifthScenario() && hasPreviouseSpaceshipReached)
        {
            return;
        }
    }
}
void Control::findSpaceshipHasReachedStatus(AStar aStar, std::vector<std::shared_ptr<Spaceship>>::iterator &spaceshipIt, std::vector<std::shared_ptr<Spaceship>> &spaceships, const std::shared_ptr<City> &des, const std::shared_ptr<City> &finalDestinationForCurrentSpaceship, bool &hasPreviouseSpaceshipReached)
{
    if (!((*spaceshipIt)->getHasReachedDestination()))
    {
        findDestinationDefenseRatioStatus(aStar, spaceshipIt, spaceships, des, finalDestinationForCurrentSpaceship, hasPreviouseSpaceshipReached);
        if (isFifthScenario() && hasPreviouseSpaceshipReached)
        {
            return;
        }
    }
    else
    {
        spaceshipIt = spaceships.erase(spaceshipIt);
    }
}

void Control::routing(AStar aStar)
{
    IdentifyPriorityEnemyTarget(aStar);
    std::vector<std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>>> reachedSpaceshipsToEachDestinationTmp(reachedSpaceshipsToEachDestination.begin(), reachedSpaceshipsToEachDestination.end());

    std::sort(reachedSpaceshipsToEachDestinationTmp.begin(), reachedSpaceshipsToEachDestinationTmp.end(), compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction);
    std::shared_ptr<City> finalDestinationForCurrentSpaceship;

    for (auto &[des, spaceships] : reachedSpaceshipsToEachDestination)
    {
        finalDestinationForCurrentSpaceship = des;
        sortSpaceshipsBasedOnDestructionInAscendingOrder(spaceships);
        bool hasPreviouseSpaceshipReached = false;
        for (auto spaceshipIt = spaceships.begin(); spaceshipIt != spaceships.end();)
        {
            findSpaceshipHasReachedStatus(aStar, spaceshipIt, spaceships, des, finalDestinationForCurrentSpaceship, hasPreviouseSpaceshipReached);
            if (isFifthScenario() && hasPreviouseSpaceshipReached)
            {
                return;
            }
        }
    }
}
bool Control::isFifthScenario()
{
    if (dataFile.getScenario() == 5)
    {
        return true;
    }
    return false;
}

bool Control::isThirdScenario()
{
    if (dataFile.getScenario() == 3)
    {
        std::cout << "third" << std::endl;
        return true;
    }
    return false;
}

void Control::IdentifyPriorityEnemyTarget(AStar aStar)
{
    for (auto spaceship : listOfSpaceships)
    {
        aStar.AStarSearch(mapWithSpies, coordsToCityPtr[spaceship->getCoordinates()], listOfAllCities[listOfAllCities.size() - 1], spaceship);
        setAStarResultsForEachSpaceship(aStar.getExistingPathsForEachSpaceship());
        initializeTrackedCitiesForEachSpaceship(spaceship, aStar);
    }
    findValidReachedDestinations(); // find the missed spaceships
    findPathBasedOnTotalDistance(aStar);
    incrementReachedSpaceshipsToEachDestination();
    setSpiesAtThePathForEachDesination(aStar); // assign the spies to path and each spaceships
}
void Control::setSpiesAtThePathForEachDesination(AStar aStar)
{
    for (auto &[spaceship, pathRes] : AStarPathsForEachSpaceship)
    {
        for (auto &path : pathRes)
        {
            numOfSpiesForEachDestinationOfEachSpaceship[spaceship][path.destination] = aStar.backTrackToFindSpies(coordsToCityPtr[spaceship->getCoordinates()], path.destination, trackedCitiesForEachSpaceship[spaceship]);
        }
    }
}
bool Control::ifDestinationHasDefenseRatio(const std::shared_ptr<City> &destination)
{
    if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(destination))
    {
        if (enemy->getDefense().getRatio() > 0) // determine whether the defense can continue working
            return true;
    }
    return false;
}
void Control::sortSpaceshipsBasedOnDestructionInAscendingOrder(std::vector<std::shared_ptr<Spaceship>> &spaceships)
{
    std::sort(spaceships.begin(), spaceships.end(), compareSpaceshipsBasedOnDestructionInAscendingOrder);
}

void Control::incrementReachedSpaceshipsToEachDestination()
{
    for (const auto &[spaceship, allPath] : AStarPathsForEachSpaceship)
    {
        for (PathResult path : allPath)
        {
            reachedSpaceshipsToEachDestination[path.destination].emplace_back(spaceship);
        }
    }
}
void Control::initializeTrackedCitiesForEachSpaceship(const std::shared_ptr<Spaceship> &spaceship, AStar aStar)
{
    trackedCitiesForEachSpaceship[spaceship] = aStar.getTrackNodes();
}

void Control::displayTheFinalResult(const std::vector<std::shared_ptr<City>> &finalRes, const std::shared_ptr<Spaceship> &spaceship)
{
    std::cout << "the final path for " << spaceship->getNameOfSpaceship() << ": ";
    for (auto finalRes : finalRes)
    {
        std::cout << "(" << finalRes->getCoordinates().first << " , " << finalRes->getCoordinates().second << ")" << " -> ";
    }
    std::cout << "final destruction: " << amountOfDestruction << std::endl;
}

void Control::setAStarResults(const std::vector<PathResult> &pathResults)
{
    AStarResults = pathResults;
}
void Control::run()
{
    initializeMap();
    std::cout << "run" << std::endl;
    if (isThirdScenario())
    {
        std::cout << "3" << std::endl;
        AStar aStar;
        routingForThirdScenario(aStar);
        std::cout << "3" << std::endl;
    }
    else if (isFifthScenario())
    {
        std::cout << "5" << std::endl;

        controlingNightsForFifthScenario();
        std::cout << "5" << std::endl;
    }
    else
    {
        std::cout << "else" << std::endl;

        AStar aStar;
        routing(aStar);
        std::cout << "else" << std::endl;
    }
}
// int main()
// {
//     Control c;
//     // c.initializePriceFile();
//     c.initializeMap();
//     // c.routing();
//     // c.routingForFifthScenario();
//     AStar aStar;
//     // c.controlingNightsForFifthScenario();
//     //  c.routing(aStar);
//     c.routingForThirdScenario(aStar);
// }