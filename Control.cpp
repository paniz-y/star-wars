#include "Control.hpp"

Control::Control()
{
    amountOfDestruction = 0;
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
std::vector<std::shared_ptr<City>> Control::readBaseCitysFromFile()
{
    std::string numberOfBaseCitysFromFile;
    mapFile >> numberOfBaseCitysFromFile >> numOfBaseCitys;

    std::string baseCityCoordinatesFromFile;
    mapFile >> baseCityCoordinatesFromFile;

    std::vector<std::pair<int, int>> baseCityCoodinatesFromFile(numOfBaseCitys);

    for (int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> baseCityCoodinatesFromFile[i].first >> baseCityCoodinatesFromFile[i].second;
    }

    std::string baseCitySpyStringFromFile;
    mapFile >> baseCitySpyStringFromFile;
    std::vector<int> baseCitySpyFromFile(numOfBaseCitys);
    for (int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> baseCitySpyFromFile[i];
    }

    std::string spaceshipString;
    mapFile >> spaceshipString;
    std::cout << spaceshipString << std::endl;
    std::string nameOfSPaceships, numberOfSpaceships;
    std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities(numOfBaseCitys);
    std::cout << numOfBaseCitys << std::endl;
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

    std::vector<std::shared_ptr<City>> baseCityForMap = initializeBaseCities(baseCityCoodinatesFromFile, baseCitySpyFromFile, spaceshipsInBaseCities);
    return baseCityForMap;
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
    std::string numberOfCivilCitysFromFile;
    mapFile >> numberOfCivilCitysFromFile >> numOfCivilCitys;

    std::vector<std::pair<int, int>> civilCityCoodinatesFromFile(numOfCivilCitys);

    std::string civilCityCoordinatesFromFile;
    mapFile >> civilCityCoordinatesFromFile;

    for (int i = 0; i < numOfCivilCitys; i++)
    {
        mapFile >> civilCityCoodinatesFromFile[i].first >> civilCityCoodinatesFromFile[i].second;
    }

    std::string civilCitySpyStringFromFile;
    std::vector<int> civilCitySpyFromFile(numOfCivilCitys);
    mapFile >> civilCitySpyStringFromFile;
    for (int i = 0; i < numOfCivilCitys; i++)
    {
        mapFile >> civilCitySpyFromFile[i];
    }

    std::vector<std::shared_ptr<City>> civilCitiesForTheMap = initializeCivilCities(civilCityCoodinatesFromFile, civilCitySpyFromFile);
    return civilCitiesForTheMap;
}
std::vector<std::shared_ptr<City>> Control::readEnemyCitysFromFile()
{
    std::string numberOfEnemyCitysFromFile;
    mapFile >> numberOfEnemyCitysFromFile >> numOfEnemyCitys;

    std::string enemyCityCoordinatesFromFile;
    mapFile >> enemyCityCoordinatesFromFile;

    std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile(numOfEnemyCitys);
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCityCoodinatesFromFile[i].first >> enemyCityCoodinatesFromFile[i].second;
    }

    std::string enemyCitySpyStringFromFile;
    std::vector<int> enemyCitySpyFromFile(numOfEnemyCitys);
    mapFile >> enemyCitySpyStringFromFile;
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCitySpyFromFile[i];
    }

    std::string enemyCityDefenseStringRatioFromFile;
    mapFile >> enemyCityDefenseStringRatioFromFile;
    std::vector<int> enemyCityDefenseRatioFromFile(numOfEnemyCitys);

    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCityDefenseRatioFromFile[i];
    }

    std::vector<Defense> enemyCitiesDefense(numOfEnemyCitys);
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        enemyCitiesDefense[i].setRatio(enemyCityDefenseRatioFromFile[i]);
    }
 
    std::vector<std::shared_ptr<City>> enemyCitiesMadeForMap = initializeEnemyCities(enemyCityCoodinatesFromFile, enemyCitySpyFromFile, enemyCitiesDefense);

    return enemyCitiesMadeForMap;
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
void Control::updateCurrentDefenseRatio(const AStarRes &finalResultForCurrentSpaceship)
{
    if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(finalResultForCurrentSpaceship.destination))
    {
        if (enemy->getDefense().getRatio() > 0)
        {
            enemy->defenseForChange().defend();
        }
    }
}
std::vector<std::shared_ptr<City>> Control::initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense)
{
    std::vector<std::shared_ptr<City>> enemyCities;
    for (int i = 0; i < enemyCityCoodinatesFromFile.size(); i++)
    {
        EnemyCity enemyCityTmp(enemyCityCoodinatesFromFile[i], enemyCitySpyFromFile[i], enemyCitiesDefense[i], true);
        listOfEnemyCities.emplace_back(enemyCityTmp);
        std::shared_ptr<EnemyCity> enemyPtrTmp = std::make_shared<EnemyCity>(enemyCityCoodinatesFromFile[i], enemyCitySpyFromFile[i], enemyCitiesDefense[i], true);
        enemyCities.emplace_back(enemyPtrTmp);
        coordsToCityPtr[enemyCityCoodinatesFromFile[i]] = enemyCities.back();
    }
    findTheFarthestEnemyCity(enemyCities);
    return enemyCities;
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
    std::cout << "allSpaceships size " << allSpaceships.size() << std::endl;
    for (int i{}; i < allSpaceships.size(); i++)
    {
        std::cout << "in base class " << allSpaceships[i]->getCoordinates().first << " " << allSpaceships[i]->getNameOfSpaceship() << std::endl;
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

    std::vector<std::shared_ptr<City>> baseCities = readBaseCitysFromFile();
    std::vector<std::shared_ptr<City>> civilCities = readCivilCitysFromFile();
    std::vector<std::shared_ptr<City>> enemyCities = readEnemyCitysFromFile();
    readMaxMapSizeFromFile();
    initializeListOfBaseAndCivilCities(baseCities, civilCities);
    mapFile.close();
    collectAllCities(baseCities, civilCities, enemyCities);
    mapWithSpies.graphMap(allCities);
}
double heuristic(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second) // calculates heuristic for A* search algorithm
{
    std::pair<int, int> firstCityCoordinates = first->getCoordinates();
    std::pair<int, int> secondCityCoordinates = second->getCoordinates();
    double distance = sqrt(pow(firstCityCoordinates.first - secondCityCoordinates.first, 2) + pow(firstCityCoordinates.second - secondCityCoordinates.second, 2));
    return distance;
}
void Control::initializeCorrespondentCityForEachSpaceship()
{
    for (int i{}; i < allSpaceships.size(); i++)
    {
        correspondentCityForEachSpaceship.emplace_back(allSpaceships[i], coordsToCityPtr[allSpaceships[i]->getCoordinates()]);
    }
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
int Control::increaseRadarResistant(std::shared_ptr<City> city, int spysDetected)
{
    if (city->getExistenceOfSpy())
    {
        spysDetected++;
    }
    return spysDetected;
}

AStarRes Control::AStar(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship)
{
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node

    nodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpies.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = DBL_MAX;
    }
    int spiesAtThePath = 0;
    while (!nodes.empty())
    {
        Node currNode = nodes.top();
        nodes.pop();

        if (currNode.currCity == destination)
        {

            spiesAtThePath = increaseRadarResistant(currNode.currCity, spiesAtThePath); // detecting whether the destination has spies
            AStarRes result = {currNode.currCity, spiesAtThePath, currNode.g, false};
            AStarResults.emplace_back(result);
            return result;
        }

        if (visitedNodeCities.find(currNode.currCity) != visitedNodeCities.end())
        {
            continue;
        }
        visitedNodeCities.insert(currNode.currCity);

        spiesAtThePath = increaseRadarResistant(currNode.currCity, spiesAtThePath); // detecting whether the city has spies

        for (auto &neighbor : mapWithSpies.getNeighbors(currNode.currCity))
        {
            double neighborGScore = neighbor.second + currNode.g;

            if (shortestDistance.find(neighbor.first) == shortestDistance.end() || neighborGScore < shortestDistance[neighbor.first])
            {
                if (heuristic(currNode.currCity, neighbor.first) > spaceship->getUncontrolledDistance())
                {
                    continue; // reprogram the spaceship if required
                }

                shortestDistance[neighbor.first] = neighborGScore;
                trackNodes[neighbor.first] = currNode.currCity;

                double neighborHScore = heuristic(neighbor.first, destination);
                nodes.push({neighbor.first, currNode.currCity, neighborGScore, neighborGScore + neighborHScore});
                AStarRes result = {currNode.currCity, spiesAtThePath, currNode.g, false};
                AStarResults.emplace_back(result);
            }
        }
    }
    AStarRes result;
    result.setCost(-1);
    result.setSpies(0);
    return result; // no rout found
}
std::vector<std::shared_ptr<City>> Control::backtrackAStarPath(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination)
{
    std::vector<std::shared_ptr<City>> path;
    if (trackNodes.empty() || trackNodes.find(destination) == trackNodes.end())
    {
        return {};
    }

    std::shared_ptr<City> current = destination;
    while (current != nullptr && current != start)
    {
        path.push_back(current);
        current = trackNodes.at(current);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

bool Control::validateRoutBasedOnUncontrolledDistance(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, const std::shared_ptr<Spaceship> &spaceship)
{
    double distance = heuristic(start, destination);
    if (spaceship->getUncontrolledDistance() >= distance)
    {
        return true;
    }
    return false;
}

void Control::findValidReachedDestinations()
{
    for (std::vector<AStarRes>::iterator it = AStarResults.begin(); it != AStarResults.end();)
    {
        if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(it->destination))
        {
            it++;
        }
        else
        {
            it = AStarResults.erase(it);
        }
    }
   
}

void Control::findPathForARadarResistantSpaceship(const std::shared_ptr<Spaceship> &spaceship)
{
    std::sort(AStarResults.begin(), AStarResults.end(), compareTwoRoutsBasedOnSpies); // sorting based on radar resistance

    for (std::vector<AStarRes>::iterator it = AStarResults.begin(); it != AStarResults.end();)
    {
        if (isSpaceshipRadarResistant(spaceship, it->numOfSpies))
        {
            it++;
        }
        else
        {
            it = AStarResults.erase(it); // deleting the pathes exceeded
        }
    }
}

void Control::findPathBasedOnTotalDistance(const std::shared_ptr<Spaceship> &spaceship)
{
    for (std::vector<AStarRes>::iterator it = AStarResults.begin(); it != AStarResults.end();)
    {
        if (heuristic(coordsToCityPtr[spaceship->getCoordinates()], it->destination) <= spaceship->getDistance())
        {
            it++;
        }
        else
        {
            it = AStarResults.erase(it); // deleting the pathes that exceeded the total distance of this spaceship
        }
    }
}

AStarRes Control::findBestDestinationBasedOnDefenseRatio()
{
    std::sort(AStarResults.begin(), AStarResults.end(), compareTwoRoutsBasedOnDefenseRatio);

    return AStarResults[0];
}

bool Control::compareTwoRoutsBasedOnSpies(const AStarRes &first, const AStarRes &second)
{
    return first.numOfSpies < second.numOfSpies;
}
bool Control::compareTwoRoutsBasedOnDefenseRatio(const AStarRes &first, const AStarRes &second)
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
void Control::routing()
{
    int cnt = 0;
    for (auto spaceship : allSpaceships)
    {
        AStarResults.clear();
        AStarRes finalResultForCurrentSpaceship;
        AStar(coordsToCityPtr[spaceship->getCoordinates()], allCities[allCities.size() - 1], spaceship);
        findValidReachedDestinations();
        findPathBasedOnTotalDistance(spaceship);
        findPathForARadarResistantSpaceship(spaceship);
        if (AStarResults.size() != 0)
        {
            finalResultForCurrentSpaceship = findBestDestinationBasedOnDefenseRatio();
        }
        else
        {
            std::cout << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << " is missed \n";
            continue;
        }
        updateCurrentDefenseRatio(finalResultForCurrentSpaceship);

        std::vector<std::shared_ptr<City>> finalRes = backtrackAStarPath(coordsToCityPtr[spaceship->getCoordinates()], finalResultForCurrentSpaceship.destination);

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
void Control::heuristicForAllCities()
{
    for (int i = 0; i < allCities.size(); i++)
    {
        for (int j = 0; j < allCities.size(); j++)
        {
            std::pair<std::shared_ptr<City>, std::shared_ptr<City>> heuristicTmpKey = std::make_pair(allCities[i], allCities[j]);
            eachCityHeuristics[heuristicTmpKey] = (heuristic(allCities[i], allCities[j]));
        }
    }

}
int main()
{
    Control c;
    c.readMapFromFile();
    c.heuristicForAllCities();
    c.routing();
}