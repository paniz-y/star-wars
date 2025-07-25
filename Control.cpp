#include "Control.hpp"

void Control::readBaseCitysFromFile()
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

    // for (int i = 0; i < numOfBaseCitys; i++)
    // {
    //     std::cout << baseCityCoodinatesFromFile[i].first << " " << baseCityCoodinatesFromFile[i].second << std::endl;
    // }

    std::string baseCitySpyStringFromFile;
    mapFile >> baseCitySpyStringFromFile;
    std::vector<int> baseCitySpyFromFile(numOfBaseCitys);
    for (int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> baseCitySpyFromFile[i];
    }

    // for (int i = 0; i < numOfBaseCitys; i++)
    // {
    //     std::cout << "baseCityspys " << baseCitySpyFromFile[i] << std::endl;
    // }

    std::string spaceshipString;
    mapFile >> spaceshipString;
    std::string nameOfSPaceships, numberOfSpaceships;
    std::vector<std::pair<int, std::string>> spaceshipsInBaseCities(numOfBaseCitys);
    for (int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> numberOfSpaceships >> spaceshipsInBaseCities[i].first >> nameOfSPaceships >> spaceshipsInBaseCities[i].second;
    }
    std::vector<std::shared_ptr<BaseCity>> baseCityForMap = initializeBaseCities(baseCityCoodinatesFromFile, baseCitySpyFromFile, spaceshipsInBaseCities);
    // for (int i = 0; i < numOfBaseCitys; i++)
    // {
    //     std::cout << numberOfSpaceships << " " << spaceshipsInBaseCities[i].first << " " << nameOfSPaceships << " " << spaceshipsInBaseCities[i].second << std::endl;
    // }
    // baseCityCoodinates.resize(numOfBaseCitys);
    // baseCityCoodinates = baseCityCoodinatesFromFile;
}
std::vector<std::shared_ptr<Spaceship>> Control::findSutableSpaceshipForBaseCities(std::vector<std::pair<int, std::string>> spaceshipsInBaseCities)
{
    std::vector<std::shared_ptr<Spaceship>> spaceshipFoundForBaseCity;
    for (int i{}; i < spaceshipsInBaseCities.size() && i < spaceshipsInBaseCities[i].first; i++)
    {
        spaceshipType type = stringToSpaceshipType(spaceshipsInBaseCities[i].second);
        switch (type)
        {
        case spaceshipType::Awing:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<Awing>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
            // return std::make_shared<Awing>();
        case spaceshipType::DeathStar:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<DeathStar>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        case spaceshipType::Mantis:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<Mantis>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        case spaceshipType::MillenniumFalcon:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<MillenniumFalcon>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        case spaceshipType::RazorCrest:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<RazorCrest>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        case spaceshipType::StarDestroyer:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<StarDestroyer>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        case spaceshipType::TieFighter:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<TieFighter>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        case spaceshipType::XwingStarFighter:
        {
            std::shared_ptr tmpSpaceship = std::make_shared<XwingStarFighter>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        }
        default:
            throw std::invalid_argument("Unknown city type: " + spaceshipsInBaseCities[i].second);
        }
    }
    return spaceshipFoundForBaseCity;
}
void Control::readCivilCitysFromFile()
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

    std::vector<std::shared_ptr<CivilCity>> civilCitiesForTheMap = initializeCivilCities(civilCityCoodinatesFromFile, civilCitySpyFromFile);
}
void Control::readEnemyCitysFromFile()
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

    // std::cout << "number " << numOfEnemyCitys << std::endl;
    std::string enemyCityDefenseStringRatioFromFile;
    mapFile >> enemyCityDefenseStringRatioFromFile;
    std::vector<int> enemyCityDefenseRatioFromFile(numOfEnemyCitys);

    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCityDefenseRatioFromFile[i];
    }

    // for (int i = 0; i < numOfEnemyCitys; i++)
    // {
    //     std::cout << "ratio " << enemyCityDefenseRatioFromFile[i] << std::endl;
    // }

    std::vector<Defense> enemyCitiesDefense(numOfEnemyCitys);
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        enemyCitiesDefense[i].setRatio(enemyCityDefenseRatioFromFile[i]);
    }

    std::vector<std::shared_ptr<EnemyCity>> enemyCitiesMadeForMap = initializeEnemyCities(enemyCityCoodinatesFromFile, enemyCitySpyFromFile, enemyCitiesDefense);
    // std::cout << "before object " << std::endl;
    // for (int i = 0; i < numOfEnemyCitys; i++)
    // {
    //     std::cout << "ratio after " << enemyCitiesDefense[i].getRatio() << std::endl;
    // }

    // enemyCityCoodinates.resize(numOfEnemyCitys);
    // enemyCityCoodinates = enemyCityCoodinatesFromFile;
}
std::vector<std::shared_ptr<EnemyCity>> Control::initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense)
{
    std::vector<std::shared_ptr<EnemyCity>> enemyCities;
    for (int i = 0; i < enemyCityCoodinatesFromFile.size(); i++)
    {
        EnemyCity enemyTmp(enemyCityCoodinatesFromFile[i], enemyCitySpyFromFile[i], enemyCitiesDefense[i]);
        enemyCities.emplace_back(enemyTmp);
    }
    return enemyCities;
}
std::vector<std::shared_ptr<BaseCity>> Control::initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::string>> spaceshipsInBaseCities)
{
    std::vector<std::shared_ptr<BaseCity>> baseCities;
    for (int i = 0; i < baseCityCoodinatesFromFile.size(); i++)
    {
        std::vector<std::shared_ptr<Spaceship>> baseCitySpaceshipType = findSutableSpaceshipForBaseCities(spaceshipsInBaseCities);
        BaseCity baseTmp(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i], baseCitySpaceshipType);
        baseCities.emplace_back(baseCities);
    }
    return baseCities;
}
std::vector<std::shared_ptr<CivilCity>> Control::initializeCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile)
{
    std::vector<std::shared_ptr<CivilCity>> civilCities;
    for (int i = 0; i < civilCityCoodinatesFromFile.size(); i++)
    {
        CivilCity civilTmp(civilCityCoodinatesFromFile[i], civilCitySpyFromFile[i]);
        civilCities.emplace_back(civilTmp);
    }
    return civilCities;
}
void Control::readMapFromFile()
{
    mapFile.open("Map.txt", std::ios::in);
    if (!mapFile.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    readBaseCitysFromFile();
    readCivilCitysFromFile();
    readEnemyCitysFromFile();

    mapFile.close();
}
double heuristic(const std::shared_ptr<City> &a, const std::shared_ptr<City> &b) // calculates heuristic for A* search algorithm
{
    std::pair<int, int> firstCityCoordinates = a->getCoordinates();
    std::pair<int, int> secondCityCoordinates = b->getCoordinates();
    double distance = sqrt(pow(firstCityCoordinates.first - secondCityCoordinates.first, 2) + pow(firstCityCoordinates.first - secondCityCoordinates.second, 2));
    return distance;
}
void Control::AStarRouting(Map map, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination) // uses A* search algorithm for routing
{

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> previousNodes; // for each node stores the previous node that has been visited
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance;             // for each node stores the shortest distance required to reach it
                                                                                    // std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> neighbor;      // stores each node and its previous one for backtracking the path
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities;                    // stores each city that has been visited as a node

    previousNodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;

    while (!previousNodes.empty())
    {
        Node currNode = previousNodes.top();
        previousNodes.pop();
        if (currNode.currCity == destination)
        {
            return;
        }
        for (auto &neighbor : map.getNeighbors(currNode.currCity))
        {
            double neighborGScore = neighbor.second + currNode.g;
            if (visitedNodeCities.find(neighbor.first) != visitedNodeCities.end() || shortestDistance[neighbor.first] < neighborGScore)
            {
                double neighborHScore = heuristic(start, neighbor.first);
                Node visited = {neighbor.first, currNode.currCity, neighborGScore, neighborHScore};
                previousNodes.emplace(visited);
                visitedNodeCities.emplace(neighbor.first);
            }
        }
    }
}
int Control::CalculateDistance()
{
}
int main()
{
    Control c;
    c.readMapFromFile();
}