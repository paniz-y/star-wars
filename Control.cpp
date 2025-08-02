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
    mapWithSpys.setMaxSize(maxMapSize);
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

    for (int i = 0; i < numOfBaseCitys; i++)
    {
        std::cout << "spaceship " << numberOfSpaceships << " " << spaceshipsInBaseCities[i].first << " " << nameOfSPaceships << " " << spaceshipsInBaseCities[i].second << std::endl;
    }
    std::vector<std::shared_ptr<City>> baseCityForMap = initializeBaseCities(baseCityCoodinatesFromFile, baseCitySpyFromFile, spaceshipsInBaseCities);
    // baseCityCoodinates.resize(numOfBaseCitys);
    // baseCityCoodinates = baseCityCoodinatesFromFile;
    return baseCityForMap;
}
std::shared_ptr<Spaceship> Control::findSuitableSpaceshipForBaseCities(std::pair<int, std::string> spaceshipsInBaseCities)
{
    // std::vector<std::shared_ptr<Spaceship>> spaceshipFoundForBaseCity;
    // std::cout << "spaceshipsInBaseCities " << spaceshipsInBaseCities.size() << std::endl;
    // for (int i{}; i < spaceshipsInBaseCities.size() && i < spaceshipsInBaseCities[i].first; i++)
    // {
    // std::cout << "slammmmmmmmmm " << spaceshipsInBaseCities.first << " " << spaceshipsInBaseCities.second << std::endl;
    spaceshipType type = stringToSpaceshipType(spaceshipsInBaseCities.second);
    switch (type)
    {
    case spaceshipType::Awing:
    {
        // std::shared_ptr<Awing> tmpSpaceship = std::make_shared<Awing>();
        // std::shared_ptr<Awing> spaceshipFoundForBaseCity = std::make_shared<Awing>();
        // allSpaceships.emplace_back(tmpSpaceship);
        return std::make_shared<Awing>();
        // std::cout <<"awwwwwwwwwwww " <<tmpSpaceship->getNameOfSpaceship() << std::endl;
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        // std::cout << "first time spaceship created " <<
        // break;
    }
        // return std::make_shared<Awing>();
    case spaceshipType::DeathStar:
    {
        // std::shared_ptr<DeathStar> tmpSpaceship = std::make_shared<DeathStar>();
        return std::make_shared<DeathStar>();
        // std::shared_ptr<DeathStar> spaceshipFoundForBaseCity = std::make_shared<DeathStar>();
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        // std::cout << "deaaaaaaaaaa "<<tmpSpaceship->getNameOfSpaceship() << std::endl;
        // allSpaceships.emplace_back(tmpSpaceship);
        // break;
    }
    case spaceshipType::Mantis:
    {
        // std::shared_ptr<Mantis> tmpSpaceship = std::make_shared<Mantis>();
        // std::shared_ptr<Mantis> spaceshipFoundForBaseCity = std::make_shared<Mantis>();
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        return std::make_shared<Mantis>();
        // std::cout << "mannnnnnnn "<<tmpSpaceship->getNameOfSpaceship() << std::endl;
        // allSpaceships.emplace_back(tmpSpaceship);
        break;
    }
    case spaceshipType::MillenniumFalcon:
    {
        // std::shared_ptr<MillenniumFalcon> tmpSpaceship = std::make_shared<MillenniumFalcon>();
        // std::shared_ptr<MillenniumFalcon> spaceshipFoundForBaseCity = std::make_shared<MillenniumFalcon>();
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        return std::make_shared<MillenniumFalcon>();
        // break;
    }
    case spaceshipType::RazorCrest:
    {
        // std::shared_ptr<RazorCrest> spaceshipFoundForBaseCity = std::make_shared<RazorCrest>();
        // std::shared_ptr<RazorCrest> tmpSpaceship = std::make_shared<RazorCrest>();
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        // std::cout <<"rrrrrrrrrrrrrr " <<tmpSpaceship->getNameOfSpaceship() << std::endl;
        // allSpaceships.emplace_back(tmpSpaceship);
        return std::make_shared<RazorCrest>();
        // break;
        // allSpaceships.emplace_back(tmpSpaceship);
    }
    case spaceshipType::StarDestroyer:
    {
        // std::shared_ptr<StarDestroyer> spaceshipFoundForBaseCity = std::make_shared<StarDestroyer>();
        // std::shared_ptr<StarDestroyer> tmpSpaceship = std::make_shared<StarDestroyer>();
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        // std::cout <<"ssssssssss " <<tmpSpaceship->getNameOfSpaceship() << std::endl;
        // allSpaceships.emplace_back(tmpSpaceship);
        return std::make_shared<StarDestroyer>();
        // break;
    }
        // allSpaceships.emplace_back(tmpSpaceship);
    case spaceshipType::TieFighter:
    {
        // std::shared_ptr<TieFighter> spaceshipFoundForBaseCity = std::make_shared<TieFighter>();
        // std::shared_ptr<TieFighter> tmpSpaceship = std::make_shared<TieFighter>();
        // allSpaceships.emplace_back(tmpSpaceship);
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        return std::make_shared<TieFighter>();
        // break;
    }
    case spaceshipType::XwingStarFighter:
    {
        // allSpaceships.emplace_back(tmpSpaceship);
        // std::shared_ptr<XwingStarFighter> spaceshipFoundForBaseCity = std::make_shared<XwingStarFighter>();
        // std::shared_ptr<XwingStarFighter> tmpSpaceship = std::make_shared<XwingStarFighter>();
        // spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
        return std::make_shared<XwingStarFighter>();
        // std::cout <<"xxxxxxxxxxxxxxx " <<tmpSpaceship->getNameOfSpaceship() << std::endl;
        // allSpaceships.emplace_back(tmpSpaceship);
        // break;
    }
    default:
        throw std::invalid_argument("Unknown city type: " + spaceshipsInBaseCities.second);
        // allSpaceships.emplace_back(tmpSpaceship);
        // }
    }
    // for(auto a: spaceshipFoundForBaseCity)
    //     std::cout << "aaaaaaaaaaaaaaaaaa " << a->getNameOfSpaceship() << std::endl;
    // std::cout <<"akhar hamechi " << spaceshipFoundForBaseCity.size() << std::endl;
    // std::cout << "akhar hamechi " << spaceshipFoundForBaseCity->getNameOfSpaceship() << std::endl;

    // return std::make_shared<Spaceship>();
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
    // for (int i = 0; i < numOfEnemyCitys; i++)
    // {
    //     std::cout << "mannnnnnnnnnnnnnnn " << enemyCitiesDefense[i].getRatio() << std::endl;
    // }
    std::vector<std::shared_ptr<City>> enemyCitiesMadeForMap = initializeEnemyCities(enemyCityCoodinatesFromFile, enemyCitySpyFromFile, enemyCitiesDefense);

    return enemyCitiesMadeForMap;
    // std::cout << "before object " << std::endl;
    // for (int i = 0; i < numOfEnemyCitys; i++)
    // {
    //     std::cout << "ratio after " << enemyCitiesDefense[i].getRatio() << std::endl;
    // }

    // enemyCityCoodinates.resize(numOfEnemyCitys);
    // enemyCityCoodinates = enemyCityCoodinatesFromFile;
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
        // std::cout << "ratio enemy in initialize " << enemyCityTmp.getDefense().getRatio() << std::endl;
        // std::cout << "ratio enemy in initialize ptr " << enemyCitiesDefense[i].getRatio() << std::endl;
        // auto coordsTmp = std::tie(enemyCityCoodinatesFromFile[i].first, enemyCityCoodinatesFromFile[i].second);
        coordsToCityPtr[enemyCityCoodinatesFromFile[i]] = enemyCities.back();
        // std::cout << " coordsToCityPtr[enemyCityCoodinatesFromFile[i]] "<< i << " " <<  coordsToCityPtr[enemyCityCoodinatesFromFile[i]]->getCoordinates().first << " " <<  coordsToCityPtr[enemyCityCoodinatesFromFile[i]]->getCoordinates().second << std::endl;
    }
    return enemyCities;
}
std::vector<std::shared_ptr<City>> Control::initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::string>> spaceshipsInBaseCities)
{
    std::vector<std::shared_ptr<City>> baseCities;
    // std::cout << "heeeeeeeeeee " << spaceshipsInBaseCities.size() << std::endl;
    for (int i = 0; i < baseCityCoodinatesFromFile.size(); i++)
    {
        std::vector<std::shared_ptr<Spaceship>> spaceshipsFoundFromBaseCities;
        for (int j = 0; j < spaceshipsInBaseCities[i].first; j++)
        {
            // std::cout << "noghre " << spaceshipsInBaseCities[i].first << std::endl;
            // std::vector <std::shared_ptr<Spaceship>> spaceshipFromBaseCity = findSuitableSpaceshipForBaseCities(spaceshipsInBaseCities[i]);
            // std::cout << "be in sorat " << a->getNameOfSpaceship() << std::endl;
            spaceshipsFoundFromBaseCities.emplace_back(findSuitableSpaceshipForBaseCities(spaceshipsInBaseCities[i]));
        }

        std::shared_ptr<BaseCity> basePtrTmp = std::make_shared<BaseCity>(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i], spaceshipsFoundFromBaseCities);

        initializeAllSpaceships(spaceshipsFoundFromBaseCities, baseCityCoodinatesFromFile[i]);
        baseCities.emplace_back(basePtrTmp);
        // std::cout << "allSpaceship.size() " << i << " " << allSpaceships.size() << std::endl;
        // BaseCity baseCityTmp(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i], allSpaceships);
        // auto coordsTmp = std::tie(baseCityCoodinatesFromFile[i].first, baseCityCoodinatesFromFile[i].second);
        coordsToCityPtr[baseCityCoodinatesFromFile[i]] = baseCities.back();
        // std::cout <<" coordsToCityPtr[baseCityCoodinatesFromFile " << i << " " << coordsToCityPtr[baseCityCoodinatesFromFile[i]]->getCoordinates().first << " " << coordsToCityPtr[baseCityCoodinatesFromFile[i]]->getCoordinates().second << std::endl;
    }
    std::cout << "allSpaceships size " << allSpaceships.size() << std::endl;
    // for (int i{}; i < allSpaceships.size(); i++)
    // {
    //     std::cout <<"in base class "<< allSpaceships[i]->getCoordinates().first << " " << allSpaceships[i]->getCoordinates().second << std::endl;
    // }
    return baseCities;
}
std::vector<std::shared_ptr<City>> Control::initializeCivilCities(std::vector<std::pair<int, int>> civilCityCoodinatesFromFile, std::vector<int> civilCitySpyFromFile)
{
    std::vector<std::shared_ptr<City>> civilCities;
    for (int i = 0; i < civilCityCoodinatesFromFile.size(); i++)
    {
        std::shared_ptr<CivilCity> civilPtrTmp = std::make_shared<CivilCity>(civilCityCoodinatesFromFile[i], civilCitySpyFromFile[i]);
        civilCities.emplace_back(civilPtrTmp);
        // auto coordsTmp = std::tie(civilCityCoodinatesFromFile[i].first, civilCityCoodinatesFromFile[i].second);
        coordsToCityPtr[civilCityCoodinatesFromFile[i]] = civilCities.back();
        // std::cout << "coordsToCityPtr[civilCityCoodinatesFromFile " << i << coordsToCityPtr[civilCityCoodinatesFromFile[i]]->getCoordinates().first << " " << coordsToCityPtr[civilCityCoodinatesFromFile[i]]->getCoordinates().second << std::endl;
    }
    return civilCities;
}
void Control::readMapFromFile()
{
    mapFile.open("testcase3.txt", std::ios::in);
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
    mapWithSpys.graphMap(collectAllCities(baseCities, civilCities, enemyCities));
    // mapWithDefenses.graphMapWithDefenses(collectAllCities(baseCities, civilCities, enemyCities));
    // std::cout << "map " << mapWithSpys.getNeighbors(baseCities[0])[0].first->getCoordinates().first << " " << mapWithSpys.getNeighbors(baseCities[0])[0].first->getCoordinates().second << std::endl;
    // std::cout <<"eki " << mapWithSpys.getNeighbors(baseCities[0])[0].second.first << " " <<mapWithSpys.getNeighbors(baseCities[0])[0].second.second << std::endl;
}
double heuristic(const std::shared_ptr<City> &a, const std::shared_ptr<City> &b) // calculates heuristic for A* search algorithm
{
    std::pair<int, int> firstCityCoordinates = a->getCoordinates();
    std::pair<int, int> secondCityCoordinates = b->getCoordinates();
    double distance = sqrt(pow(firstCityCoordinates.first - secondCityCoordinates.first, 2) + pow(firstCityCoordinates.second - secondCityCoordinates.second, 2));
    return distance;
}
void Control::initializeCorrespondentCityForEachSpaceship()
{
    for (int i{}; i < allSpaceships.size(); i++)
    {
        correspondentCityForEachSpaceship.emplace_back(allSpaceships[i], coordsToCityPtr[allSpaceships[i]->getCoordinates()]);
    }

    // for (int i{}; i < allSpaceships.size(); i++)
    // {
    //     std::cout << correspondentCityForEachSpaceship[i].first->getNameOfSpaceship() << " " << correspondentCityForEachSpaceship[i].second->getCoordinates().first << " " << correspondentCityForEachSpaceship[i].second->getCoordinates().second << std::endl;
    // }
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
AStarRes Control::AStarRoutingForSpys(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship) // uses A* search algorithm for routing
{

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodes; // stores each node and sortes them based on f score
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance;     // for each node stores the shortest distance required to reach it
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities;            // stores each city that has been visited as a node
    nodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpys.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = DBL_MAX;
    }
    int radarResistanceSoFar = /*spaceship->getRadarResistance()*/ 0;
    int radarResistanceTmp = radarResistanceSoFar;
    std::cout << "radarResistanceSoFar " << radarResistanceSoFar << std::endl;
    std::shared_ptr<City> previouseVisitedCity;
    while (!nodes.empty())
    {

        Node currNode = nodes.top();
        nodes.pop();
        // std::cout << "previouseVisitedCity " << currNode.currCity->getCoordinates().first <<" " <<currNode.currCity->getCoordinates().second << std::endl;
        previouseVisitedCity = currNode.currCity;
        std::cout << "cheking before decreaseRadarResistant " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;

        radarResistanceTmp = increaseRadarResistant(currNode.currCity, radarResistanceTmp);
        // radarResistanceSoFar = radarResistanceTmp;
        AStarRes res;
        if (isSpaceshipRadarResistant(spaceship, radarResistanceTmp))
        {
            std::cout << "if enemy " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;
            if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(currNode.currCity)) // defense presence
            {
                std::cout << "enemy city " << std::endl;
                // controlDestructions(spaceship->getDestruction());
                //  res.isDestroyed = true;
                res.setDestroyed(true);
                std::cout << "laaaaaaaaaaaaaaa4 " << res.isDestroyed << std::endl;
            }
            if (currNode.currCity == destination)
            {
                std::cout << "final " << currNode.g << std::endl;
                std::cout << "radarResistanceTmp " << radarResistanceTmp << std::endl;
                // spaceship->setRadarResistance(radarResistanceTmp);
                radarResistanceSoFar = radarResistanceTmp;
                // res = {destination, radarResistanceSoFar, currNode.g};
                res.destination = destination;
                res.numOfObstacles = radarResistanceSoFar;
                res.cost = currNode.g;
                std::cout << "laaaaaaaaaaaaaaa " << res.isDestroyed << std::endl;
                return res; // rout found
            }

            // std::cout << "after decreaseRadarResistant " << radarResistanceTmp << std::endl;
            // std::cout << "after if isSpaceshipRadarResistant(radarResistanceTmp) "<< isSpaceshipRadarResistant(radarResistanceTmp) << std::endl;
            for (auto &neighbor : mapWithSpys.getNeighbors(currNode.currCity))
            {
                // std::cout << "currNode " << currNode.g << std::endl;

                double neighborGScore = neighbor.second.first + currNode.g;
                // std::cout << "nieghborGscore " << neighborGScore << std::endl;
                // std::cout << "nieghbor in heuristic " << neighbor.first->getCoordinates().first << " " << neighbor.first->getCoordinates().second << std::endl;
                // std::cout << "out of the if heuristic(neighbor.first, destination)" << heuristic(start, destination) << std::endl;
                // std::cout << "spaceship->getControlLessDictance()) " <<spaceship->getControlLessDictance() << std::endl;

                if ((visitedNodeCities.find(neighbor.first) == visitedNodeCities.end() || neighborGScore < shortestDistance[neighbor.first]) && heuristic(start, destination) <= spaceship->getControlLessDictance())
                {
                    double neighborHScore = heuristic(neighbor.first, destination);
                    Node visited = {neighbor.first, currNode.currCity, neighborGScore, neighborHScore};
                    nodes.emplace(visited);
                    shortestDistance[neighbor.first] = neighborGScore;
                    radarResistanceSoFar = radarResistanceTmp;
                    // std::cout << "radarResistanceSoFar " << radarResistanceSoFar << std::endl;
                }
                // std::cout << "after second if\n";
            }

            visitedNodeCities.emplace(currNode.currCity);
        }
        else
        {
            // std::cout << "in the else " << std::endl;
            // previouseVisitedCity = currNode.currCity;
            radarResistanceSoFar = radarResistanceTmp;
            AStarRes res = {previouseVisitedCity, radarResistanceSoFar, -2, false};
            return res; // out of radar resitante
        }

        // std::cout << "after for \n";
    }
    AStarRes res = {start, radarResistanceSoFar, -1, false};
    return res; // no rout wihtout exceeding controlless distance
}
AStarRes Control::AStarRoutingForDefenses(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship) // uses A* search algorithm for routing
{

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodes; // stores each node and sortes them based on f score
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance;     // for each node stores the shortest distance required to reach it
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities;            // stores each city that has been visited as a node

    nodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpys.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = DBL_MAX;
    }
    std::shared_ptr<City> previouseVisitedCity;
    while (!nodes.empty())
    {
        Node currNode = nodes.top();
        nodes.pop();

        // std::cout <<
        // std::cout << "after if " << std::endl;
        previouseVisitedCity = currNode.currCity;
        std::cout << "in defense curr " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;
        int defenseRatioSoFar = /*enemy->getDefense().getRatio()*/ 0;
        int defenseRatioTmp = defenseRatioSoFar;

        if (currNode.currCity == destination)
        {
            // std::cout << "final " << currNode.g << std::endl;
            // return currNode.g;
            std::cout << "inja" << std::endl;
            AStarRes res = {destination, defenseRatioSoFar, currNode.g, false};
            return res;
        }
        for (auto &neighbor : mapWithSpys.getNeighbors(currNode.currCity))
        {
            // std::cout << "currNode " << currNode.g << std::endl;
            double neighborGScore = neighbor.second.second + currNode.g;
            std::cout << heuristic(start, destination) << " heuristic" << std::endl;
            if ((visitedNodeCities.find(neighbor.first) == visitedNodeCities.end() || (neighborGScore < shortestDistance[neighbor.first])) && heuristic(start, destination) <= spaceship->getControlLessDictance())
            {
                if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(currNode.currCity)) // defense presence
                {
                    // if (neighbor.second.second == mapWithDefenses.getMaxSize() * 2)
                    // {
                    //     jgkhgj
                    // }
                    std::cout << "defenseRatioTmpppppppppppppppppppppppp " << defenseRatioTmp << std::endl;
                    // controlDestructions(spaceship->getDestruction());
                    if (/*enemy->getDefense().getRatio() <= 0*/ /*defenseRatioTmp <= 0*/ defenseRatioTmp >= enemy->getDefense().getRatio())
                    {
                        std::cout << "jjjjjjjjjjjj" << std::endl;
                        // mapWithSpys.removeDefense(currNode.currCity);
                        AStarRes res = {enemy, defenseRatioTmp, currNode.g, true}; // out of defense ratio
                        return res;
                    }
                    else
                    {
                        // enemy->getDefense().defend();
                        defenseRatioTmp++;
                        defenseRatioSoFar = defenseRatioTmp;
                        AStarRes res = {enemy, defenseRatioSoFar, -3};
                        return res; // the spaceship is missed
                    }
                    std::cout << "after defenddddddddddddd " << enemy->getDefense().getRatio() << std::endl;
                }
                double neighborHScore = heuristic(neighbor.first, destination);
                Node visited = {neighbor.first, currNode.currCity, neighborGScore, neighborHScore};
                nodes.emplace(visited);
                shortestDistance[neighbor.first] = neighborGScore;
            }
            // std::cout << "after second if\n";
        }
        visitedNodeCities.emplace(currNode.currCity);

        // std::cout << "after for \n";
    }
    AStarRes res = {previouseVisitedCity, 0, -1, false};
    return res; // no rout wihtout exceeding controlless distance
}
void Control::initializeListOfBaseAndCivilCities(std::vector<std::shared_ptr<City>> baseCities, std::vector<std::shared_ptr<City>> civilCities)
{
    listOfBaseAndCivilCities.insert(listOfBaseAndCivilCities.end(), baseCities.begin(), baseCities.end());
    listOfBaseAndCivilCities.insert(listOfBaseAndCivilCities.end(), civilCities.begin(), civilCities.end());
}
std::vector<std::shared_ptr<City>> Control::collectAllCities(const std::vector<std::shared_ptr<City>> &baseCities, const std::vector<std::shared_ptr<City>> &civilCities, const std::vector<std::shared_ptr<City>> &enemyCities)
{
    std::vector<std::shared_ptr<City>> allCities;
    allCities.insert(allCities.end(), baseCities.begin(), baseCities.end());
    allCities.insert(allCities.end(), civilCities.begin(), civilCities.end());
    allCities.insert(allCities.end(), enemyCities.begin(), enemyCities.end());

    return allCities;
}
// void Control::routing()
// {
//     initializeCorrespondentCityForEachSpaceship();
//     for (auto spaceship : allSpaceships)
//     {
//         // std::cout << "befor for" << std::endl;
//         for (auto enemy : listOfEnemyCities)
//         {
//             // std::cout << "before A star\n";
//             // std::cout << "befor " << std::endl;
//             // std::cout << "spaceship->getCoordinates()" << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
//             // std::cout << "enemy.getCoordinates()" << enemy.getCoordinates().first << " " << enemy.getCoordinates().second << std::endl;
//             // std::cout << "spaceship " << spaceship->getTypeOfSpaceship() << std::endl;
//             routingResults.emplace_back(AStarRoutingForSpys(coordsToCityPtr[spaceship->getCoordinates()], coordsToCityPtr[enemy.getCoordinates()], spaceship));
//             // std::cout << "A* for s first " << routingResults.back().first << std::endl;
//             // std::cout << "A* for s second " << routingResults.back().second << std::endl;
//             if (routingResults.back().first == -1) // exceeding the controlless distance
//             {
//                 // std::cout << "here in if " << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
//                 for (auto civilOrBase : listOfBaseAndCivilCities)
//                 {
//                     // std::cout << "civil " <<
//                     routingResults.emplace_back(AStarRoutingForSpys(previouseVisitedCity, civilOrBase, spaceship));
//                 }
//             }
//             if (routingResults.back().first == -2) //  out of radar resistant
//             {
//                 // std::cout << "jooda " << std::endl;
//                 std::cout << "A* for d " << AStarRoutingForDefenses(previouseVisitedCity, coordsToCityPtr[enemy.getCoordinates()], spaceship) << std::endl;
//             }
//         }
//     }
//     for (auto res : routingResults)
//     {
//         std::cout << "res f " << res.first << " res s " << res.second << std::endl;
//     }
// }
// void Control::routing()
// {
//     initializeCorrespondentCityForEachSpaceship();

//     for (auto spaceship : allSpaceships)
//     {
//         std::cout << "befor for spaceship" << allSpaceships.size() << std::endl;
//         for (auto enemy : listOfEnemyCities)
//         {
//             do
//             {
//                 routingResultsForSpys.emplace_back(AStarRoutingForSpys(coordsToCityPtr[spaceship->getCoordinates()], coordsToCityPtr[enemy.getCoordinates()], spaceship));
//                 std::cout << "A* for s first " << routingResultsForSpys.back().first << std::endl;
//                 std::cout << "A* for s second " << routingResultsForSpys.back().second << std::endl;

//                 if (routingResultsForSpys.back().first == -1) // exceeding the controlless distance
//                 {
//                     // std::cout << "here in if " << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
//                     for (auto civilOrBase : listOfBaseAndCivilCities)
//                     {
//                         if (civilOrBase != previouseVisitedCity)
//                         {
//                             std::cout << "civil " << previouseVisitedCity->getCoordinates().first << " " << previouseVisitedCity->getCoordinates().second << std::endl;
//                             std::cout << "civil or Base " << civilOrBase->getCoordinates().first << " " << civilOrBase->getCoordinates().second << std::endl;
//                             routingResultsForSpys.emplace_back(AStarRoutingForSpys(previouseVisitedCity, civilOrBase, spaceship));
//                             std::cout << "after in civil back ro cout mikonim " << routingResultsForSpys.back().first << std::endl;
//                             // if (routingResultsForSpys.back().first != -1 && routingResultsForSpys.back().first != -2)
//                             //     break;
//                         }
//                     }
//                     std::cout << "as in for dare dar miad\n";
//                 }
//                 std::cout << "as if bia birron " << routingResultsForSpys.back().first << std::endl;
//             } while (routingResultsForSpys.back().first == -1);
//             std::cout << "before A star aval \n";

//             if (routingResultsForSpys.back().first != -2)
//             {
//                 std::cout << "routingResultsForSpys.back().first " << routingResultsForSpys.back().first << std::endl;
//                 routingResultsForSpys.emplace_back(AStarRoutingForSpys(previouseVisitedCity, coordsToCityPtr[enemy.getCoordinates()], spaceship));
//             }
//             // std::cout << "befor " << std::endl;
//             // std::cout << "spaceship->getCoordinates()" << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
//             // std::cout << "enemy.getCoordinates()" << enemy.getCoordinates().first << " " << enemy.getCoordinates().second << std::endl;
//             // std::cout << "spaceship " << spaceship->getTypeOfSpaceship() << std::endl;
//             else if (routingResultsForSpys.back().first == -2) //  out of radar resistant
//             {
//                 std::cout << "to esle if" << std::endl;
//                 do
//                 {
//                     // std::cout << "jooda " << std::endl;
//                     std::cout << "maaaaaaaaaaaaaa " << previouseVisitedCity->getCoordinates().first << " " << previouseVisitedCity->getCoordinates().second << std::endl;
//                     std::cout << "destination " << coordsToCityPtr[enemy.getCoordinates()]->getCoordinates().first << " " << coordsToCityPtr[enemy.getCoordinates()]->getCoordinates().second << std::endl;
//                     int a = AStarRoutingForDefenses(previouseVisitedCity, coordsToCityPtr[enemy.getCoordinates()], spaceship);
//                     std::cout << "a in defense map " << a << std::endl;
//                     routingResultsForDefense.emplace_back(AStarRoutingForDefenses(previouseVisitedCity, coordsToCityPtr[enemy.getCoordinates()], spaceship));

//                     std::cout << "routingResultsForDefense " << routingResultsForDefense.back() << std::endl;
//                     if (routingResultsForDefense.back() == -1) // exceeding the controlless distance
//                     {
//                         std::cout << "here in if " << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
//                         for (auto civilOrBase : listOfBaseAndCivilCities)
//                         {
//                             if (civilOrBase != previouseVisitedCity)
//                             {
//                                 std::cout << "civil " << routingResultsForDefense.emplace_back(AStarRoutingForDefenses(previouseVisitedCity, civilOrBase, spaceship));
//                             }
//                         }
//                     }
//                     else
//                         break;

//                 } while (routingResultsForDefense.back() != -1);
//             }
//         }
//     }
// }
void Control::routing()
{
    for (auto spaceship : allSpaceships)
    {
        while (true)
        {
            if (findEnemyCity(coordsToCityPtr[spaceship->getCoordinates()], spaceship) >= 0)
            {
                std::cout << bestRoutForEachSpaceship[spaceship][0].cost << " cost" << bestRoutForEachSpaceship[spaceship][0].destination->getCoordinates().first << " des "
                          << bestRoutForEachSpaceship[spaceship][0].destination->getCoordinates().second << " des"
                          << bestRoutForEachSpaceship[spaceship][0].numOfObstacles << " obstacles" << std::endl;
                spaceship->setRadarResistance(spaceship->getRadarResistance() - bestRoutForEachSpaceship[spaceship].back().numOfObstacles);
                std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance()" << std::endl;
                return;
            }
            if (bestRoutForEachSpaceship[spaceship].back().cost == -1)
            {
                findBaseOrCivilCity(bestRoutForEachSpaceship[spaceship].back().destination, spaceship);
                spaceship->setRadarResistance(spaceship->getRadarResistance() -  bestRoutForEachSpaceship[spaceship].back().numOfObstacles);
                std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance()" << std::endl;
            }
            findEnemyCity(coordsToCityPtr[spaceship->getCoordinates()], spaceship);
            spaceship->setRadarResistance(spaceship->getRadarResistance() -  bestRoutForEachSpaceship[spaceship].back().numOfObstacles);
            std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance()" << std::endl;
        }
    }
    for (auto a : AStarResults)
    {
        std::cout << "des f " << a.destination->getCoordinates().first << " des s " << a.destination->getCoordinates().second << " num of " << a.numOfObstacles << " cost " << a.cost << "dstruction " << a.isDestroyed << std::endl;
    }
}

bool Control::isSpaceshipRadarResistant(std::shared_ptr<Spaceship> spaceship, int spaceshipRadarResistance)
{
    bool isResistance = (spaceshipRadarResistance < spaceship->getRadarResistance()) ? true : false;
    return isResistance;
}
void Control::controlDestructions(int des)
{
    amountOfDestruction += des;
}
int Control::increaseRadarResistant(std::shared_ptr<City> city, int spysDetected)
{
    // int resistance = city->getExistenceOfSpy() ? (spaceshipRadarResistance--) : spaceshipRadarResistance;
    // return resistance;

    if (city->getExistenceOfSpy())
    {
        spysDetected++;
    }
    return spysDetected;
}

int Control::findEnemyCity(const std::shared_ptr<City> &start, const std::shared_ptr<Spaceship> &spaceship)
{
    std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance()" << std::endl;
    if (spaceship->getRadarResistance() > 0)
    {
        std::cout << "be defense nemirese" << std::endl;

        for (auto enemy : listOfEnemyCities)
        {
            AStarResults.emplace_back(AStarRoutingForSpys(start, coordsToCityPtr[enemy.getCoordinates()], spaceship));
        }
    }
    else
    {
        for (auto enemy : listOfEnemyCities)
        {
            std::cout << "be defense mirese" << std::endl;
            AStarResults.emplace_back(AStarRoutingForDefenses(start, coordsToCityPtr[enemy.getCoordinates()], spaceship));
        }
    }

    std::cout << "find enemy" << std::endl;

    return chooseBestRoutSoFar(spaceship);
}
int Control::findBaseOrCivilCity(const std::shared_ptr<City> &start, const std::shared_ptr<Spaceship> &spaceship)
{
    for (auto baseOrCivil : listOfBaseAndCivilCities)
    {
        AStarResults.emplace_back(AStarRoutingForSpys(start, baseOrCivil, spaceship));
    }
    return chooseBestRoutSoFar(spaceship);
    std::cout << bestRoutForEachSpaceship[spaceship][0].cost << " cost" << bestRoutForEachSpaceship[spaceship][0].destination->getCoordinates().first << " des "
              << bestRoutForEachSpaceship[spaceship][0].destination->getCoordinates().second << " des"
              << bestRoutForEachSpaceship[spaceship][0].numOfObstacles << " obstacles" << std::endl;
}

int Control::chooseBestRoutSoFar(const std::shared_ptr<Spaceship> &spaceship)
{
    std::sort(AStarResults.begin(), AStarResults.end(), compareTwoRoutsBasedOnCost);
    for (auto rout : AStarResults)
    {
        if (rout.cost >= 0) // the spaceship has reached a destination
        {
            bestRoutForEachSpaceship[spaceship].emplace_back(rout);
            return rout.cost;
        }
    }
    for (auto rout : AStarResults)
    {
        if (rout.cost == -1) // the spaceship hasn't been able to reached a destination without exceeding the controlless distance
        {
            bestRoutForEachSpaceship[spaceship].emplace_back(rout);
            return rout.cost;
        }
    }
    std::sort(AStarResults.begin(), AStarResults.end(), compareTwoRoutsBasedOnObstacles);

    bestRoutForEachSpaceship[spaceship].emplace_back(AStarResults[0]);
    return -2;
}

bool Control::compareTwoRoutsBasedOnCost(const AStarRes &first, const AStarRes &second)
{
    return first.cost < second.cost;
}
bool Control::compareTwoRoutsBasedOnObstacles(const AStarRes &first, const AStarRes &second)
{
    return first.numOfObstacles < second.numOfObstacles;
}

int main()
{
    Control c;
    c.readMapFromFile();
    c.routing();
    std::cout << "destruction " << c.amountOfDestruction << std::endl;
}