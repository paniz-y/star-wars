#include "Control.hpp"

Control::Control()
{
    amountOfDestruction = 0;
}
void Control::readScenarioNumberFromFile()
{
    std::string scenarioString;
    mapFile >> scenarioString >> scenario;
    std::cout << "scenario " << scenario << std::endl;
}
void Control::readMaxMapSizeFromFile()
{
    std::string maxOfMapString;
    mapFile >> maxOfMapString;
    int maxMapSize;
    mapFile >> maxMapSize;
    mapWithSpies.setMaxSize(maxMapSize);
    mapWithDefenses.setMaxSize(maxMapSize);
}
std::vector<std::string> Control::readUnknownSpaceshipesFromFile()
{
    std::string existingSpaceshipsString, totalNumberString, spaceshipsStringName;
    int existingSpies, totalNumberOfSpachships;
    mapFile >> existingSpaceshipsString;
    mapFile >> totalNumberString >> totalNumberOfSpachships;

    std::vector<std::string> existingSpaceships(totalNumberOfSpachships);
    mapFile >> spaceshipsStringName;
    for (int i = 0; i < totalNumberOfSpachships; i++)
    {
        if (!(mapFile >> existingSpaceships[i]))
        {
            std::cerr << "Failed to read capacity at index " << i << std::endl;
            break;
        }
        else
        {
            std::cout << "Read capacity[" << i << "] = " << existingSpaceships[i] << std::endl;
        }
    }
    return existingSpaceships;
}
std::vector<int> Control::readBaseCpacitesFromFile()
{
    std::string basesCapacityStringFromFile;
    mapFile >> basesCapacityStringFromFile;

    std::vector<int> basesCapacityFromFile(numOfBaseCities);
    std::cout << "basesCapacityStringFromFile " << basesCapacityFromFile.size() << std::endl;
    for (int i = 0; i < numOfBaseCities; i++)
    {
        if (!(mapFile >> basesCapacityFromFile[i]))
        {
            std::cerr << "Failed to read capacity at index " << i << std::endl;
            break;
        }
        else
        {
            std::cout << "Read capacity[" << i << "] = " << basesCapacityFromFile[i] << std::endl;
        }
    }
    std::cout << "end of func\n";
    return basesCapacityFromFile;
}
std::vector<std::shared_ptr<City>> Control::readBaseCitysFromFile()
{
    std::vector<std::shared_ptr<City>> baseCityForMap;
    readNumberOfBasesFromFile();
    std::vector<std::pair<int, int>> baseCityCoodinatesFromFile(numOfBaseCities);
    baseCityCoodinatesFromFile = readBaseCorrdinatesFromFile();

    std::vector<int> baseCitySpyFromFile(numOfBaseCities);
    baseCitySpyFromFile = readSpiesOfBasesFromFile();

    if (scenario != 3)
    {
        std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities(numOfBaseCities);
        spaceshipsInBaseCities = readSpaceshipsOfBasesFromFile();
        baseCityForMap = initializeBaseCities(baseCityCoodinatesFromFile, baseCitySpyFromFile, spaceshipsInBaseCities);
    }
    else
    {
        std::vector<int> baseCitiesCapacity(numOfBaseCities);
        baseCitiesCapacity = readBaseCpacitesFromFile();
        std::vector<std::string> spaceshipsToBeDivided = readUnknownSpaceshipesFromFile();
        allSpaceships = initializeUnknownSpaceships(spaceshipsToBeDivided);
        baseCityForMap = initializeBaseCitiesWithOutSpaceships(baseCityCoodinatesFromFile, baseCitySpyFromFile);
    }
    return baseCityForMap;
}
void Control::readNumberOfBasesFromFile()
{
    std::string numberOfBaseCitysFromFile;
    mapFile >> numberOfBaseCitysFromFile >> numOfBaseCities;
}
std::vector<std::pair<int, std::vector<std::string>>> Control::readSpaceshipsOfBasesFromFile()
{
    std::string spaceshipString;
    mapFile >> spaceshipString;
    std::cout << spaceshipString << std::endl;
    std::string nameOfSPaceships, numberOfSpaceships;
    std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities(numOfBaseCities);
    std::cout << numOfBaseCities << std::endl;
    for (int i = 0; i < spaceshipsInBaseCities.size(); i++)
    {
        mapFile >> numberOfSpaceships >> spaceshipsInBaseCities[i].first;
        mapFile >> nameOfSPaceships;
        for (int j = 0; j < spaceshipsInBaseCities[i].first; j++)
        {
            std::string spaceshipTmpName;
            mapFile >> spaceshipTmpName;
            spaceshipsInBaseCities[i].second.emplace_back(spaceshipTmpName);
        }
    }
    return spaceshipsInBaseCities;
}
std::vector<int> Control::readSpiesOfBasesFromFile()
{
    std::string baseCitySpyStringFromFile;
    mapFile >> baseCitySpyStringFromFile;
    std::vector<int> baseCitySpyFromFile(numOfBaseCities);
    for (int i = 0; i < numOfBaseCities; i++)
    {
        mapFile >> baseCitySpyFromFile[i];
    }
    return baseCitySpyFromFile;
}
std::vector<std::pair<int, int>> Control::readBaseCorrdinatesFromFile()
{
    std::string baseCityCoordinatesFromFile;
    mapFile >> baseCityCoordinatesFromFile;
    std::vector<std::pair<int, int>> baseCityCoodinatesFromFile(numOfBaseCities);

    for (int i = 0; i < numOfBaseCities; i++)
    {
        mapFile >> baseCityCoodinatesFromFile[i].first >> baseCityCoodinatesFromFile[i].second;
    }
    return baseCityCoodinatesFromFile;
}
std::shared_ptr<Spaceship> Control::findSuitableSpaceshipForBaseCities(std::string spaceshipsInBaseCities)
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
    readNumberOfCivilCitiesFromFile();

    std::vector<std::pair<int, int>> civilCityCoodinatesFromFile(numOfCivilCities);
    civilCityCoodinatesFromFile = readCivilCoordinatesFromFile();

    std::vector<int> civilCitySpyFromFile(numOfCivilCities);
    civilCitySpyFromFile = readCivilSpiesFromFile();

    std::vector<std::shared_ptr<City>> civilCitiesForTheMap = initializeCivilCities(civilCityCoodinatesFromFile, civilCitySpyFromFile);
    return civilCitiesForTheMap;
}
void Control::readNumberOfCivilCitiesFromFile()
{
    std::string numberOfCivilCitysFromFile;
    mapFile >> numberOfCivilCitysFromFile >> numOfCivilCities;
}
std::vector<std::pair<int, int>> Control::readCivilCoordinatesFromFile()
{
    std::vector<std::pair<int, int>> civilCityCoodinatesFromFile(numOfCivilCities);

    std::string civilCityCoordinatesFromFile;
    mapFile >> civilCityCoordinatesFromFile;

    for (int i = 0; i < numOfCivilCities; i++)
    {
        mapFile >> civilCityCoodinatesFromFile[i].first >> civilCityCoodinatesFromFile[i].second;
    }

    return civilCityCoodinatesFromFile;
}
std::vector<int> Control::readCivilSpiesFromFile()
{
    std::string civilCitySpyStringFromFile;
    std::vector<int> civilCitySpyFromFile(numOfCivilCities);
    mapFile >> civilCitySpyStringFromFile;
    for (int i = 0; i < numOfCivilCities; i++)
    {
        mapFile >> civilCitySpyFromFile[i];
    }

    return civilCitySpyFromFile;
}

std::vector<std::shared_ptr<City>> Control::readEnemyCitysFromFile()
{
    readNumberOfEnemyCitiesFromFile();

    std::vector<std::pair<int, int>> enemyCityCoordinatesFromFile(numOfEnemyCitys);
    enemyCityCoordinatesFromFile = readEnemyCitiesCoordinatesFromFile();

    std::vector<int> enemyCitySpyFromFile(numOfEnemyCitys);
    enemyCitySpyFromFile = readEnemyCitiesSpiesFromFile();

    std::vector<int> enemyCityDefenseRatioFromFile(numOfEnemyCitys);
    enemyCityDefenseRatioFromFile = readEnemyCitiesDefenseRatioFromFile();

    std::vector<Defense> enemyCitiesDefense(numOfEnemyCitys);
    enemyCitiesDefense = readEnemyCitiesDefenseFromFile(enemyCityDefenseRatioFromFile);

    std::vector<std::shared_ptr<City>> enemyCitiesMadeForMap = initializeEnemyCities(enemyCityCoordinatesFromFile, enemyCitySpyFromFile, enemyCitiesDefense);
    enemiesAsCity = enemyCitiesMadeForMap;
    return enemyCitiesMadeForMap;
}
void Control::readNumberOfEnemyCitiesFromFile()
{
    std::string numberOfEnemyCitysFromFile;
    mapFile >> numberOfEnemyCitysFromFile >> numOfEnemyCitys;
}
std::vector<std::pair<int, int>> Control::readEnemyCitiesCoordinatesFromFile()
{
    std::string enemyCityCoordinatesStringFromFile;
    mapFile >> enemyCityCoordinatesStringFromFile;

    std::vector<std::pair<int, int>> enemyCityCoordinatesFromFile(numOfEnemyCitys);
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCityCoordinatesFromFile[i].first >> enemyCityCoordinatesFromFile[i].second;
    }
    return enemyCityCoordinatesFromFile;
}
std::vector<int> Control::readEnemyCitiesSpiesFromFile()
{
    std::vector<int> enemyCitySpyFromFile(numOfEnemyCitys);
    std::string enemyCitySpyStringFromFile;
    mapFile >> enemyCitySpyStringFromFile;
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCitySpyFromFile[i];
    }
    return enemyCitySpyFromFile;
}
std::vector<int> Control::readEnemyCitiesDefenseRatioFromFile()
{
    std::string enemyCityDefenseStringRatioFromFile;
    mapFile >> enemyCityDefenseStringRatioFromFile;
    std::vector<int> enemyCityDefenseRatioFromFile(numOfEnemyCitys);

    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCityDefenseRatioFromFile[i];
    }
    return enemyCityDefenseRatioFromFile;
}
std::vector<Defense> Control::readEnemyCitiesDefenseFromFile(std::vector<int> enemyCityDefenseRatioFromFile)
{
    std::vector<Defense> enemyCitiesDefense(numOfEnemyCitys);
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        enemyCitiesDefense[i].setRatio(enemyCityDefenseRatioFromFile[i]);
    }
    return enemyCitiesDefense;
}
void Control::findTheFarthestEnemyCity(std::vector<std::shared_ptr<City>> &enemies)
{
    std::sort(enemies.begin(), enemies.end(), compareEnemiesBasedOnDistance);
}
bool Control::compareEnemiesBasedOnDistance(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second)
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
std::vector<std::shared_ptr<City>> Control::initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoordinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense)
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
std::vector<std::shared_ptr<Spaceship>> Control::initializeUnknownSpaceships(std::vector<std::string> spaceships)
{
    std::vector<std::shared_ptr<Spaceship>> unknownSpaceships;
    for (int i = 0; i < spaceships.size(); i++)
    {
        unknownSpaceships.emplace_back(findSuitableSpaceshipForBaseCities(spaceships[i]));
    }
    return unknownSpaceships;
}
std::vector<std::shared_ptr<City>> Control::initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities)
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
std::vector<std::shared_ptr<City>> Control::initializeBaseCitiesWithOutSpaceships(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile)
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
std::vector<std::shared_ptr<City>> Control::initializeCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile)
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
void Control::readMapFromFile()
{
    mapFile.open("testcase7.txt", std::ios::in);
    if (!mapFile.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }
    readScenarioNumberFromFile();
    std::vector<std::shared_ptr<City>> baseCities = readBaseCitysFromFile();
    std::vector<std::shared_ptr<City>> civilCities = readCivilCitysFromFile();
    std::vector<std::shared_ptr<City>> enemyCities = readEnemyCitysFromFile();
    readMaxMapSizeFromFile();
    initializeListOfBaseAndCivilCities(baseCities, civilCities);
    mapFile.close();
    collectAllCities(baseCities, civilCities, enemyCities);
    mapWithSpies.graphMap(allCities);
}

void Control::initializeAllSpaceships(std::vector<std::shared_ptr<Spaceship>> spaceships, std::pair<int, int> coordinates)
{
    int allSpaceshipsSize = allSpaceships.size();

    for (int i{}; i < spaceships.size(); i++)
    {
        allSpaceships.emplace_back(spaceships[i]);
    }
    for (int i{}; i < spaceships.size(); i++)
    {
        allSpaceships[allSpaceshipsSize + i]->setCoordinates(coordinates);
    }
}

void Control::initializeListOfBaseAndCivilCities(std::vector<std::shared_ptr<City>> baseCities, std::vector<std::shared_ptr<City>> civilCities)
{
    listOfBaseAndCivilCities.insert(listOfBaseAndCivilCities.end(), baseCities.begin(), baseCities.end());
    listOfBaseAndCivilCities.insert(listOfBaseAndCivilCities.end(), civilCities.begin(), civilCities.end());
}
void Control::collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities)
{

    allCities.insert(allCities.end(), baseCities.begin(), baseCities.end());
    allCities.insert(allCities.end(), civilCities.begin(), civilCities.end());
    allCities.insert(allCities.end(), enemyCities.begin(), enemyCities.end());
}

bool Control::isSpaceshipRadarResistant(std::shared_ptr<Spaceship> spaceship, int numOfSpies)
{
    if (numOfSpies < spaceship->getRadarResistance())
        return true;
    return false;
}
void Control::controlDestructions(int des)
{
    amountOfDestruction += des;
}

void Control::findValidReachedDestinations()
{
    for (auto &spaceship : AStarPathsForEachSpaceship)
    {
        for (auto it = spaceship.second.begin(); it != spaceship.second.end();)
        {
            if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(it->destination))
            {
                it++;
            }
            else
            {
                it = spaceship.second.erase(it); // remove the path not reaching the enemy city
            }
        }
    }
    // std::cout << "===== Paths After filterAndSortPathsBasedOnDestination() =====\n";
    // for (const auto &spaceship : AStarPathsForEachSpaceship)
    // {
    //     std::cout << "Spaceship " << spaceship.first->getNameOfSpaceship() << " " << spaceship.first->getCoordinates().first << " valid paths:\n";
    //     for (const auto &path : spaceship.second)
    //     {
    //         if (auto enemy = std::dynamic_pointer_cast<EnemyCity>(path.destination))
    //         {
    //             std::cout << "  -> Enemy city: " << enemy->getCoordinates().first << "\n";
    //         }
    //         std::cout << "------------------------------------------------------\n";
    //     }
    // }
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
    // std::cout << "===== Paths After filterAndSortPathsBasedOnSpies() =====\n";

    // for (const auto &kv : AStarPathsForEachSpaceship)
    // {
    //     auto spaceship = kv.first;
    //     const auto &paths = kv.second;

    //     std::cout << "Spaceship: " << spaceship->getNameOfSpaceship()
    //               << " at " << spaceship->getCoordinates().first << " | Remaining Paths: " << paths.size() << "\n";

    //     for (const auto &path : paths)
    //     {
    //         std::cout << "  - Destination: ";
    //         if (auto enemy = std::dynamic_pointer_cast<EnemyCity>(path.destination))
    //         {
    //             std::cout << enemy->getCoordinates().first;
    //         }
    //         else
    //         {
    //             std::cout << "Non-Enemy City";
    //         }

    //         std::cout << " | numOfSpies: " << path.numOfSpies << "\n";
    //     }
    //     std::cout << "------------------------------------------------------\n";
    // }

    // std::cout << "=======================================================\n";
}

void Control::findPathBasedOnTotalDistance()
{
    for (auto &mapSpaceship : AStarPathsForEachSpaceship)
    {
        for (auto it = mapSpaceship.second.begin(); it != mapSpaceship.second.end();)
        {
            if (aStar.heuristic(coordsToCityPtr[mapSpaceship.first->getCoordinates()], it->destination) <= mapSpaceship.first->getDistance())
            {
                it++;
            }
            else
            {
                it = mapSpaceship.second.erase(it); // deleting the pathes that exceeded the total distance of this spaceship
            }
        }
    }
}

PathResult Control::findBestDestinationBasedOnDefenseRatio(std::shared_ptr<Spaceship> spaceship)
{
    if (AStarPathsForEachSpaceship.find(spaceship) == AStarPathsForEachSpaceship.end() || AStarPathsForEachSpaceship.find(spaceship)->second.empty())
    {
        throw std::runtime_error("No paths found for this spaceship");
    }

    auto it = AStarPathsForEachSpaceship.find(spaceship);
    std::sort(it->second.begin(), it->second.end(), compareTwoRoutsBasedOnDefenseRatio);

    return it->second.front();
}

bool Control::compareTwoRoutsBasedOnSpies(const PathResult &first, const PathResult &second)
{
    return first.numOfSpies < second.numOfSpies;
}
bool Control::compareTwoRoutsBasedOnDefenseRatio(const PathResult &first, const PathResult &second)
{
    if (std::shared_ptr<EnemyCity> firstEnemy = std::dynamic_pointer_cast<EnemyCity>(first.destination))
    {
        if (std::shared_ptr<EnemyCity> secondEnemy = std::dynamic_pointer_cast<EnemyCity>(second.destination))
        {
            return firstEnemy->getDefense().getRatio() < secondEnemy->getDefense().getRatio();
        }
    }
    return false;
}

bool Control::compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction(const std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> &first, const std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>> &second)
{
    if (std::shared_ptr<EnemyCity> firstEnemy = std::dynamic_pointer_cast<EnemyCity>(first.first))
    {
        if (std::shared_ptr<EnemyCity> secondEnemy = std::dynamic_pointer_cast<EnemyCity>(second.first))
        {
            int numOfReachedSpaceshipsFirst = first.second.size() - firstEnemy->getDefense().getRatio();
            int numOfReachedSpaceshipsSecond = second.second.size() - secondEnemy->getDefense().getRatio();
            // std::cout << numOfReachedSpaceshipsFirst << " numOfReachedSpaceshipsFirst" << numOfReachedSpaceshipsSecond <<" numOfReachedSpaceshipsSecond" << std::endl;
            // std::cout << (numOfReachedSpaceshipsFirst > numOfReachedSpaceshipsSecond) << std::endl;
            return numOfReachedSpaceshipsFirst > numOfReachedSpaceshipsSecond;
        }
    }
    return false;
}

bool Control::compareSpaceshipsBasedOnDestructionInAscendingOrder(const std::shared_ptr<Spaceship> &first, const std::shared_ptr<Spaceship> &second)
{
    std::cout << first->getDestruction() << " first->getDestruction()" << std::endl;
    std::cout << second->getDestruction() << " second->getDestruction()" << std::endl;

    return first->getDestruction() < second->getDestruction();
}

bool Control::compareSpaceshipsBasedOnDestructionInDescendingOrder(const std::shared_ptr<Spaceship> &first, const std::shared_ptr<Spaceship> &second)
{
    return first->getDestruction() > second->getDestruction();
}

void Control::findPathBasedOnMaxLength(const std::shared_ptr<Spaceship> &spaceship)
{
    for (std::vector<PathResult>::iterator it = AStarResults.begin(); it != AStarResults.end();)
    {
        if (it->maxPathLengthWithNoReprogram <= spaceship->getUncontrolledDistance())
        {
            it++;
        }
        else
        {
            it = AStarResults.erase(it); // deleting the pathes that exceeded the max length a spaceship can take without being reprogrammed
        }
    }
}
void Control::routingForThirdScenario()
{
    int cnt = 0;

    // for(auto enemy: listOfEnemyCities)
    // {
    //     std::shared_ptr<City> city = enemy;
    //     numOfReachedSpaceshipsToEachCity[enemy] = 0;
    // }
    for (auto spaceship : allSpaceships)
    {
        std::cout << "routingForThirdScenario" << std::endl;
        AStarResults.clear();
        PathResult finalResultForCurrentSpaceship;
        for (auto baseORCivil : listOfBaseAndCivilCities)
        {
            aStar.AStarSearchForUnKnownSpaceship(mapWithSpies, coordsToCityPtr[spaceship->getCoordinates()], allCities[allCities.size() - 1], spaceship);
            setAStarResults(aStar.getPathResults(), aStar.getExistingPathsForEachSpaceship());
            findValidReachedDestinations();
            findPathBasedOnMaxLength(spaceship);
        }

        for (auto res : AStarResults)
        {
            if (res.maxPathLengthWithNoReprogram)
                std::cout << "333333 " << *(res.maxPathLengthWithNoReprogram) << " " << res.destination->getCoordinates().first << std::endl;
            numOfReachedSpaceshipsToEachDestination[res.destination]++;
        }
        //     findValidReachedDestinations();
        //     findPathBasedOnTotalDistance(spaceship);
        //     findPathForARadarResistantSpaceship(spaceship);
        //     if (AStarResults.size() != 0)
        //     {
        //         finalResultForCurrentSpaceship = findBestDestinationBasedOnDefenseRatio();
        //     }
        //     else
        //     {
        //         std::cout << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << " is missed \n";
        //         continue;
        //     }
        //     updateCurrentDefenseRatio(finalResultForCurrentSpaceship);

        //     std::vector<std::shared_ptr<City>> finalRes = aStar.backtrackAStarPath(coordsToCityPtr[spaceship->getCoordinates()], finalResultForCurrentSpaceship.destination);

        //     controlDestructions(spaceship->getDestruction());

        //     std::cout << cnt << " the spaceship is ";
        //     displayTheFinalResult(finalRes);
        //     cnt++;
        // }
        // std::cout << "final destruction " << amountOfDestruction << std::endl;
    }
}
std::vector<std::pair<int, int>> Control::updateSpiesAfterEachNight()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, allCities.size()); // shrink the number generated by gen to a range that can be used for numberOfSpies

    std::shuffle(allCities.begin(), allCities.end(), gen);

    int randomNumberOfSpies = distrib(gen); // new random number of spies

    std::vector<std::pair<int, int>> newSpiesCoordinates(randomNumberOfSpies);

    for (int i = 0; i < randomNumberOfSpies; i++)
        newSpiesCoordinates[i] = allCities[i]->getCoordinates();

    for (int i = 0; i < randomNumberOfSpies; i++)
        std::cout << "newSpiesCoordinates " << newSpiesCoordinates[i].first << " " << newSpiesCoordinates[i].second << std::endl;

    return newSpiesCoordinates;
}
void Control::updateSpiesCoordinatesAfterEachNight(std::vector<std::pair<int, int>> spies)
{
    for (int i = 0; i < spies.size(); i++)
    {
        if (spies[i] == allCities[i]->getCoordinates())
        {
            allCities[i]->setExistingSpy(true);
        }
    }
}
void Control::removeAllSpiesAfterEachNight()
{
    for (int i = 0; i < allCities.size(); i++)
    {
        allCities[i]->setExistingSpy(false);
    }
}
void Control::updateDefenseRatioAfterEachNight()
{
    for (auto &cities : allCities)
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
// void Control::routingForFifthScenario()
// {
//     sortSpaceshipsBasedOnDestructionInAscendingOrder(allSpaceships);
//     // initializeNumOfReachedSpaceshipsToEachDestination();
//     IdentifyPriorityEnemyTarget();
//     for (auto &spaceship : allSpaceships)
//     {
//         if (AStarPathsForEachSpaceship[spaceship].size() == 0) // after all validations no path is left for the spaceship
//             continue;

//         PathResult finalResultForCurrentSpaceship;
//         std::vector<std::pair<std::shared_ptr<City>, int>> reachedSpaceshipsToEachDestination(numOfReachedSpaceshipsToEachDestination.begin(), numOfReachedSpaceshipsToEachDestination.end());
//         // std::sort(reachedSpaceshipsToEachDestination.begin(), reachedSpaceshipsToEachDestination.end(), compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction);

//         // for (auto a : reachedSpaceshipsToEachDestination)
//         // {
//         //     std::cout << a.first->getCoordinates().first << " 701 " << a.second << std::endl;
//         // }
//         // std::cout << spaceship->getNameOfSpaceship() << std::endl;
//         // for (auto &a : AStarPathsForEachSpaceship)
//         // {
//         //     for (auto &b : a.second)
//         //         std::cout << "astar " << a.first->getNameOfSpaceship() << " " << b.destination->getCoordinates().first << " " << b.numOfSpies << std::endl;
//         // }
//         // std::cout << "size " << reachedSpaceshipsToEachDestination.size() << " size 2 " << AStarPathsForEachSpaceship.size() << std::endl;
//         for (auto res : AStarPathsForEachSpaceship[spaceship])
//         {
//             for (auto &reached : reachedSpaceshipsToEachDestination)
//             {
//                 if (res.destination == reached.first)
//                 {

//                     // std::cout << "des " << res.destination->getCoordinates().first << " " << reached.first->getCoordinates().first << std::endl;
//                     finalResultForCurrentSpaceship = res;
//                     // std::cout << "ghabl " << finalResultForCurrentSpaceship.destination->getCoordinates().first << " num mof spies " << res.numOfSpies << std::endl;
//                     if (!ifDestinationHasDefenseRatio(res.destination))
//                     {
//                         sortSpaceshipsBasedOnDestructionInDecendingOrder(allSpaceships);
//                     }
//                     if (!isSpaceshipRadarResistant(spaceship, res.numOfSpies) && ifDestinationHasDefenseRatio(res.destination))
//                     {
//                         // the spaceship has reached the destination being seen while that enemy destination has still got defense so the spaceship is missed
//                         // updateCurrentDefenseRatio(finalResultForCurrentSpaceship);
//                     }
//                     // std::cout << "salam" << std::endl;

//                     break;
//                 }
//             }
//         }

//         if (!isSpaceshipRadarResistant(spaceship, finalResultForCurrentSpaceship.numOfSpies) && ifDestinationHasDefenseRatio(finalResultForCurrentSpaceship.destination))
//         {
//             continue;
//         }

//         // the spaceship has reached destination and caused destruction

//         // updateCurrentDefenseRatio(finalResultForCurrentSpaceship);

//         std::vector<std::shared_ptr<City>> finalpathResult = aStar.backtrackAStarPath(coordsToCityPtr[spaceship->getCoordinates()], finalResultForCurrentSpaceship.destination, trackedCitiesForEachSpaceship[spaceship]);

//         controlDestructions(spaceship->getDestruction());

//         std::cout << spaceship->getNameOfSpaceship() << std::endl;

//         displayTheFinalResult(finalpathResult); // display the final path and destruction
//         std::cout << "finallllllllllll " << std::endl;
//     }
// }

void Control::routingForFifthScenario()
{

    // initializeNumOfReachedSpaceshipsToEachDestination();
    IdentifyPriorityEnemyTarget();
    std::vector<std::pair<std::shared_ptr<City>, int>> reachedSpaceshipsToEachDestination(numOfReachedSpaceshipsToEachDestination.begin(), numOfReachedSpaceshipsToEachDestination.end());
    std::vector<std::pair<std::shared_ptr<City>, std::vector<std::shared_ptr<Spaceship>>>> reachedSpaceshipsToEachDestinationTmp(ReachedSpaceshipsToEachDestination.begin(), ReachedSpaceshipsToEachDestination.end());

    std::sort(reachedSpaceshipsToEachDestinationTmp.begin(), reachedSpaceshipsToEachDestinationTmp.end(), compareTwoRoutsBasedOnSpaceshipsThatCausedDestroction);
    std::shared_ptr<City> finalDestinationForCurrentSpaceship;
    for (auto &[des, spaceships] : ReachedSpaceshipsToEachDestination)
    {
        finalDestinationForCurrentSpaceship = des;
        sortSpaceshipsBasedOnDestructionInAscendingOrder(spaceships);
        for(auto s : spaceships)
        {
            std::cout << s->getNameOfSpaceship() << " ";
        }
        std::cout << std::endl;
        for (auto spaceshipIt = spaceships.begin(); spaceshipIt != spaceships.end();)
        {
            if (!ifDestinationHasDefenseRatio(des))
            {
                std::cout << " too !ifDestinationHasDefenseRatio(des)" << std::endl;
                std::vector<std::shared_ptr<City>> finalpathResult = aStar.backtrackAStarPath(coordsToCityPtr[spaceships.back()->getCoordinates()], finalDestinationForCurrentSpaceship, trackedCitiesForEachSpaceship[spaceships.back()]);

                controlDestructions(spaceships.back()->getDestruction());
                std::cout << des->getCoordinates().first << " (des)" << std::endl;

                std::cout << spaceships.back()->getNameOfSpaceship() << std::endl;

                displayTheFinalResult(finalpathResult); // display the final path and destruction
                std::cout << "finallllllllllll " << std::endl;
                spaceships.pop_back();
                return;
                break;
            }
            else
            {
                // the spaceship has reached the destination being seen while that enemy destination has still got defense so the spaceship is missed
                if (isSpaceshipRadarResistant((*spaceshipIt), aStar.getNumOfSpiesForEachDestinationOfEachSpaceship()[(*spaceshipIt)][des]))
                {
                    std::cout << " too isSpaceshipRadarResistant" << std::endl;
                    std::vector<std::shared_ptr<City>> finalpathResult = aStar.backtrackAStarPath(coordsToCityPtr[(*spaceshipIt)->getCoordinates()], finalDestinationForCurrentSpaceship, trackedCitiesForEachSpaceship[(*spaceshipIt)]);

                    controlDestructions((*spaceshipIt)->getDestruction());

                    std::cout << (*spaceshipIt)->getNameOfSpaceship() << std::endl;

                    displayTheFinalResult(finalpathResult); // display the final path and destruction
                    std::cout << "finallllllllllll " << std::endl;
                    spaceshipIt = spaceships.erase(spaceshipIt);
                    return;
                    break;
                }
                updateCurrentDefenseRatio(finalDestinationForCurrentSpaceship);
                spaceshipIt = spaceships.erase(spaceshipIt);
            }
        }
    }
}

void Control::IdentifyPriorityEnemyTarget()
{
    for (auto spaceship : allSpaceships)
    {
        aStar.AStarSearch(mapWithSpies, coordsToCityPtr[spaceship->getCoordinates()], allCities[allCities.size() - 1], spaceship);
        setAStarResults(aStar.getPathResults(), aStar.getExistingPathsForEachSpaceship()); // set the results collected by Astar
        initializeTrackedCitiesForEachSpaceship(spaceship);
    }
    findValidReachedDestinations(); // find the missed spaceships

    findPathBasedOnTotalDistance();
    incrementNumOfReachedSpaceshipsToEachDestination();
    // findPathForARadarResistantSpaceship();
}
bool Control::ifDestinationHasDefenseRatio(const std::shared_ptr<City> &destination)
{
    // std::cout << "yekkkkk\n";
    // std::cout << "destiantion 707 " << destination->getCoordinates().first << std::endl;
    if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(destination))
    {
        // std::cout << "ratio " << enemy->getDefense().getRatio() << std::endl;
        if (enemy->getDefense().getRatio() > 0) // determine whether the defense can continue working
            return true;
    }
    return false;
}
void Control::sortSpaceshipsBasedOnDestructionInAscendingOrder(std::vector<std::shared_ptr<Spaceship>> &spaceships)
{
    std::sort(spaceships.begin(), spaceships.end(), compareSpaceshipsBasedOnDestructionInAscendingOrder);
}
void Control::sortSpaceshipsBasedOnDestructionInDecendingOrder(std::vector<std::shared_ptr<Spaceship>> spaceships)
{
    std::sort(spaceships.begin(), spaceships.end(), compareSpaceshipsBasedOnDestructionInDescendingOrder);
}
void Control::initializeNumOfReachedSpaceshipsToEachDestination()
{
    for (auto enemy : listOfEnemyCities)
    {
        numOfReachedSpaceshipsToEachDestination[enemy] = 0;
    }
}
void Control::incrementNumOfReachedSpaceshipsToEachDestination()
{
    for (const auto &[spaceship, allPath] : AStarPathsForEachSpaceship)
    {
        // std::cout << spaceship->getNameOfSpaceship() << " iterate umap ";
        for (PathResult path : allPath)
        {
            // std::cout << path.destination->getCoordinates().first << " ";
            numOfReachedSpaceshipsToEachDestination[path.destination]++;
            ReachedSpaceshipsToEachDestination[path.destination].emplace_back(spaceship);
        }
        // std::cout << std::endl;
        // ;
    }
    // for (auto &spaceship : AStarPathsForEachSpaceship)
    // {
    //     for (auto &path : spaceship.second)
    //         std::cout << spaceship.first->getNameOfSpaceship() << path.destination->getCoordinates().first << " " << path.destination << std::endl;
    // }
    // for (auto a : numOfReachedSpaceshipsToEachDestination)
    // {
    //     std::cout << a.first << " " << a.first->getCoordinates().first << " " << a.second << " too incrementNumOfReachedSpaceshipsToEachDestination" << std::endl;
    // }
    // for (auto &spaceship : AStarPathsForEachSpaceship)
    // {
    //     for (auto &path : spaceship.second)
    //         numOfReachedSpaceshipsToEachDestination[path.destination]++;
    // }
    for (auto a : numOfReachedSpaceshipsToEachDestination)
    {
        std::cout << a.first << " " << a.first->getCoordinates().first << " " << a.second << "  bad too incrementNumOfReachedSpaceshipsToEachDestination" << std::endl;
    }
}
void Control::initializeTrackedCitiesForEachSpaceship(const std::shared_ptr<Spaceship> &spaceship)
{
    trackedCitiesForEachSpaceship[spaceship] = aStar.getTrackNodes();
    // for(auto &a : trackedCitiesForEachSpaceship[spaceship])
    // {
    //     std::cout << "fffff "<<a.first->getCoordinates().first << " " << a.second->getCoordinates().first << std::endl;
    //     // for(auto &b : )
    // }
}

void Control::routing()
{
    int cnt = 0;
    for (auto spaceship : allSpaceships)
    {
        AStarResults.clear();
        PathResult finalResultForCurrentSpaceship;
        aStar.AStarSearch(mapWithSpies, coordsToCityPtr[spaceship->getCoordinates()], allCities[allCities.size() - 1], spaceship);
        setAStarResults(aStar.getPathResults(), aStar.getExistingPathsForEachSpaceship());
        findValidReachedDestinations();
        findPathBasedOnTotalDistance();
        findPathForARadarResistantSpaceship();
        if (AStarResults.size() != 0)
        {
            finalResultForCurrentSpaceship = findBestDestinationBasedOnDefenseRatio(spaceship);
        }
        else
        {
            std::cout << "spaceship " << spaceship->getNameOfSpaceship() << " at " << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << " is missed \n";
            continue;
        }
        // updateCurrentDefenseRatio(finalResultForCurrentSpaceship);

        std::vector<std::shared_ptr<City>> finalRes = aStar.backtrackAStarPath(coordsToCityPtr[spaceship->getCoordinates()], finalResultForCurrentSpaceship.destination, trackedCitiesForEachSpaceship[spaceship]);

        controlDestructions(spaceship->getDestruction());

        std::cout << cnt << " the spaceship is ";
        displayTheFinalResult(finalRes);
        cnt++;
    }
    std::cout << "final destruction " << amountOfDestruction << std::endl;
}
void Control::displayTheFinalResult(std::vector<std::shared_ptr<City>> finalRes)
{
    std::cout << "the final path : ";
    for (auto finalRes : finalRes)
    {
        std::cout << finalRes->getCoordinates().first << " " << finalRes->getCoordinates().second << "-> ";
    }
    std::cout << "final destruction " << amountOfDestruction << std::endl;
}

void Control::setAStarResults(std::vector<PathResult> pathResults, std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> existingPathsForEachSpaceship)
{
    AStarPathsForEachSpaceship = existingPathsForEachSpaceship;
    AStarResults = pathResults;
}

int main()
{
    Control c;
    c.readMapFromFile();
    // c.routing();
    c.routingForFifthScenario();
}