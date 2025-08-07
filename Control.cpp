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
    mapFile.open("testcase6.txt", std::ios::in);
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
    mapWithSpys.graphMap(allCities);
    // mapWithDefenses.graphMapWithDefenses(collectAllCities(baseCities, civilCities, enemyCities));
    // std::cout << "map " << mapWithSpys.getNeighbors(baseCities[0])[0].first->getCoordinates().first << " " << mapWithSpys.getNeighbors(baseCities[0])[0].first->getCoordinates().second << std::endl;
    // std::cout <<"eki " << mapWithSpys.getNeighbors(baseCities[0])[0].second.first << " " <<mapWithSpys.getNeighbors(baseCities[0])[0].second.second << std::endl;
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
void Control::AStarRoutingForSpys(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship) // uses A* search algorithm for routing
{

    // std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodes; // stores each node and sortes them based on f score
    // std::unordered_map<std::shared_ptr<City>, double> shortestDistance;     // for each node stores the shortest distance required to reach it
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node

    std::cout << "eachCityHeuristics[{allCities[0], allCities[allCities.size()]}] " << eachCityHeuristics[{allCities[0], allCities[allCities.size() - 1]}] << std::endl;
    nodes.push({start, nullptr, 0, eachCityHeuristics[{allCities[0], allCities[allCities.size() - 1]}]});

    shortestDistance[start] = 0;

    for (auto &neighbor : mapWithSpys.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = DBL_MAX;
    }

    // int radarResistanceSoFar = /*spaceship->getRadarResistance()*/ 0;
    // int radarResistanceTmp = radarResistanceSoFar;
    // std::cout << "radarResistanceSoFar " << radarResistanceSoFar << std::endl;
    std::shared_ptr<City> previouseVisitedCity;
    while (!nodes.empty())
    {

        Node currNode = nodes.top();
        nodes.pop();
        // std::cout << "destinaaaaaaaaaaaaaaaation " << destination->getCoordinates().first << " " << destination->getCoordinates().second << std::endl;
        std::cout << "currrrrrrrrrrrrrrrrrNodeeeeeeeeeeee " << currNode.currCity->getCoordinates().first << " " << currNode.prevCity->getCoordinates().first << std::endl;
        previouseVisitedCity = currNode.currCity;
        // std::cout << "cheking before decreaseRadarResistant " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;

        // radarResistanceTmp = increaseRadarResistant(currNode.currCity, radarResistanceTmp);
        //  radarResistanceSoFar = radarResistanceTmp;
        AStarRes res;
        // std::cout << "cheking before isSpaceshipRadarResistant " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;
        // std::cout << "isSpaceshipRadarResistanttttttt(spaceship, radarResistanceTmp) " << isSpaceshipRadarResistant(spaceship, radarResistanceTmp) << std::endl;
        // if (isSpaceshipRadarResistant(spaceship, radarResistanceTmp))
        // {
        std::cout << "if enemy " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;
        // if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(currNode.currCity)) // defense presence
        // {
        //     std::cout << "enemy city " << std::endl;
        //     // controlDestructions(spaceship->getDestruction());
        //     //  res.isDestroyed = true;
        //     res.setDestroyed(true);
        //     std::cout << "laaaaaaaaaaaaaaa4 " << res.isDestroyed << std::endl;
        // }
        if (currNode.currCity == destination)
        {
            // std::cout << "to gscore " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;
            // std::cout << "final " << currNode.g << std::endl;
            // std::cout << "radarResistanceTmp " << radarResistanceTmp << std::endl;
            // spaceship->setRadarResistance(radarResistanceTmp);
            // radarResistanceSoFar = radarResistanceTmp;
            // res = {destination, radarResistanceSoFar, currNode.g};
            res.destination = destination;
            // res.numOfObstacles = radarResistanceSoFar;
            // res.cost = currNode.g;
            std::cout << "laaaaaaaaaaaaaaa " << res.isDestroyed << std::endl;
            AStarResultForEachCity[start].emplace_back(res); // rout found

            // return res;
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

            if ((visitedNodeCities.find(neighbor.first) == visitedNodeCities.end() || neighborGScore < shortestDistance[neighbor.first]) /*&& heuristic(start, destination) <= spaceship->getControlLessDictance()*/)
            {
                double neighborHScore = heuristic(neighbor.first, destination);
                Node visited = {neighbor.first, currNode.currCity, neighborGScore, neighborHScore};
                nodes.emplace(visited);
                shortestDistance[neighbor.first] = neighborGScore;
                std::cout << neighbor.first->getCoordinates().first << " " << currNode.currCity->getCoordinates().first << "vvvvvvvvvvvvvvvvvvvvvv" << std::endl;
                trackNodes[neighbor.first] = currNode.currCity;
                // radarResistanceSoFar = radarResistanceTmp;
                //  std::cout << "radarResistanceSoFar " << radarResistanceSoFar << std::endl;
            }
            // std::cout << "after second if\n";
        }

        visitedNodeCities.emplace(currNode.currCity);
        //}
        // else
        // {
        //     // std::cout << "in the else " << std::endl;
        //     // previouseVisitedCity = currNode.currCity;
        //     radarResistanceSoFar = radarResistanceTmp;
        //     // std::cout << "spyyyyyy else " << radarResistanceSoFar << std::endl;
        //     AStarRes res = {previouseVisitedCity, radarResistanceSoFar, -2, false};
        //     // std::cout << " res.cost " << res.cost << std::endl;
        //     // return res;
        //     AStarResultForEachCity[start].emplace_back(res); // out of radar resitante
        // }

        // std::cout << "after for \n";
    }
    // AtStarRes res = {start, -1, false};
    // ASarResultForEachCity[start].emplace_back(res); // no rout wihtout exceeding controlless distance
    // return res;
}
// AStarRes Control::AStarRoutingForDefenses(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship) // uses A* search algorithm for routing
// {

//     // std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodes; // stores each node and sortes them based on f score
//     // std::unordered_map<std::shared_ptr<City>, double> shortestDistance;     // for each node stores the shortest distance required to reach it
//     std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node

//     nodes.push({start, nullptr, 0, heuristic(start, destination)});
//     shortestDistance[start] = 0;
//     for (auto &neighbor : mapWithSpys.getNeighbors(start))
//     {
//         shortestDistance[neighbor.first] = DBL_MAX;
//     }
//     std::shared_ptr<City> previouseVisitedCity;
//     while (!nodes.empty())
//     {
//         Node currNode = nodes.top();
//         nodes.pop();

//         // std::cout <<
//         // std::cout << "after if " << std::endl;
//         previouseVisitedCity = currNode.currCity;
//         std::cout << "in defense curr " << currNode.currCity->getCoordinates().first << " " << currNode.currCity->getCoordinates().second << std::endl;
//         int defenseRatioSoFar = /*enemy->getDefense().getRatio()*/ 0;
//         int defenseRatioTmp = defenseRatioSoFar;

//         if (currNode.currCity == destination)
//         {
//             // std::cout << "final " << currNode.g << std::endl;
//             // return currNode.g;
//             std::cout << "inja" << std::endl;
//             AStarRes res = {destination, defenseRatioSoFar, currNode.g, false};
//             return res;
//         }
//         for (auto &neighbor : mapWithSpys.getNeighbors(currNode.currCity))
//         {
//             // std::cout << "currNode " << currNode.g << std::endl;
//             double neighborGScore = neighbor.second.second + currNode.g;
//             std::cout << heuristic(start, destination) << " heuristic" << std::endl;
//             if ((visitedNodeCities.find(neighbor.first) == visitedNodeCities.end() || (neighborGScore < shortestDistance[neighbor.first])) && heuristic(start, destination) <= spaceship->getControlLessDictance())
//             {
//                 if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(currNode.currCity)) // defense presence
//                 {
//                     // if (neighbor.second.second == mapWithDefenses.getMaxSize() * 2)
//                     // {
//                     //     jgkhgj
//                     // }
//                     std::cout << "defenseRatioTmpppppppppppppppppppppppp " << defenseRatioTmp << std::endl;
//                     // controlDestructions(spaceship->getDestruction());
//                     if (/*enemy->getDefense().getRatio() <= 0*/ /*defenseRatioTmp <= 0*/ defenseRatioTmp >= enemy->getDefense().getRatio())
//                     {
//                         std::cout << "jjjjjjjjjjjj" << std::endl;
//                         // mapWithSpys.removeDefense(currNode.currCity);
//                         AStarRes res = {enemy, defenseRatioTmp, currNode.g, true}; // out of defense ratio
//                         return res;
//                     }
//                     else
//                     {
//                         // enemy->getDefense().defend();
//                         defenseRatioTmp++;
//                         defenseRatioSoFar = defenseRatioTmp;
//                         std::cout << "return\n";
//                         AStarRes res = {enemy, defenseRatioSoFar, -3};
//                         return res; // the spaceship is missed
//                     }
//                     std::cout << "after defenddddddddddddd " << enemy->getDefense().getRatio() << std::endl;
//                 }
//                 double neighborHScore = heuristic(neighbor.first, destination);
//                 Node visited = {neighbor.first, currNode.currCity, neighborGScore, neighborHScore};
//                 nodes.emplace(visited);
//                 shortestDistance[neighbor.first] = neighborGScore;
//             }
//             // std::cout << "after second if\n";
//         }
//         visitedNodeCities.emplace(currNode.currCity);

//         // std::cout << "after for \n";
//     }
//     AStarRes res = {previouseVisitedCity, 0, -1, false};
//     return res; // no rout wihtout exceeding controlless distance
// }
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
/*void Control::routing()
{
    for (auto spaceship : allSpaceships)
    {
        while (true)
        {
            if (findEnemyCity(coordsToCityPtr[spaceship->getCoordinates()], spaceship) >= 0)
            {
                std::cout << "maaaaaaaaaaaaaaaaaaa\n";
                std::cout << bestRoutForEachSpaceship[spaceship].back().cost << " cost " << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().first << " des "
                          << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().second << " des "
                          << bestRoutForEachSpaceship[spaceship].back().numOfObstacles << " obstacles " << std::endl;
                std::cout << "befor in enemy find city get resistance " << spaceship->getRadarResistance() << std::endl;

                spaceship->setRadarResistance(spaceship->getRadarResistance() - bestRoutForEachSpaceship[spaceship].back().numOfObstacles);

                std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance() in enemy if " << std::endl;
                if (bestRoutForEachSpaceship[spaceship].back().cost == -3)
                {
                    std::cout << "the spaceship is missied in enemy\n";
                    return;
                }
                return;
            }
            if (bestRoutForEachSpaceship[spaceship].back().cost == -1)
            {
                std::cout << "aval civil " << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().first << " " << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().second << std::endl;

                findBaseOrCivilCity(bestRoutForEachSpaceship[spaceship].back().destination, spaceship);

                // spaceship->setRadarResistance(spaceship->getRadarResistance() - bestRoutForEachSpaceship[spaceship].back().numOfObstacles);

                std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance() doovom " << std::endl;
                std::cout << bestRoutForEachSpaceship[spaceship].back().cost << " cost inja bad " << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().first << " des "
                          << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().second << " des"
                          << bestRoutForEachSpaceship[spaceship].back().numOfObstacles << " obstacles " << std::endl;
                std::cout << "befor in civil based rader resistance " << spaceship->getRadarResistance() << std::endl;

                // spaceship->setRadarResistance(spaceship->getRadarResistance() - bestRoutForEachSpaceship[spaceship].back().numOfObstacles);

                std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance() in civil if " << std::endl;
                if (bestRoutForEachSpaceship[spaceship].back().cost == -3)
                {
                    std::cout << "the spaceship is missied in civil\n";
                    return;
                }
            }
            std::cout << "dafe aval\n";
            findEnemyCity(bestRoutForEachSpaceship[spaceship].back().destination, spaceship);
            // spaceship->setRadarResistance(spaceship->getRadarResistance() - bestRoutForEachSpaceship[spaceship].back().numOfObstacles);

            std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance() sevoom " << std::endl;
            std::cout << bestRoutForEachSpaceship[spaceship].back().cost << " cost " << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().first << " des "
                      << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().second << " des "
                      << bestRoutForEachSpaceship[spaceship].back().numOfObstacles << " obstacles " << std::endl;
            // spaceship->setRadarResistance(spaceship->getRadarResistance() - bestRoutForEachSpaceship[spaceship].back().numOfObstacles);
            std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance() << out of if " << std::endl;
            if (bestRoutForEachSpaceship[spaceship].back().cost == -3)
            {
                std::cout << "the spaceship is missied\n";
                return;
            }
        }
    }
    for (auto a : AStarResults)
    {
        std::cout << "des fffffffffffffffffffffffffffff " << a.destination->getCoordinates().first << " des s " << a.destination->getCoordinates().second << " num of " << a.numOfObstacles << " cost " << a.cost << "dstruction " << a.isDestroyed << std::endl;
    }
}
*/
bool Control::isSpaceshipRadarResistant(std::shared_ptr<Spaceship> spaceship, int numOfSpys)
{
    // bool isResistance = (spaceshipRadarResistance < spaceship->getRadarResistance()) ? true : false;
    std::cout << "resictannnnnnnnnnnn " << numOfSpys << " badiiiiiiiiii " << spaceship->getRadarResistance() << std::endl;
    if (numOfSpys < spaceship->getRadarResistance())
        return true;
    return false;
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

AStarRes Control::AStar(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship)
{
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node

    nodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpys.getNeighbors(start))
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
            std::cout << "spy " << spiesAtThePath << std::endl;
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

        for (auto &neighbor : mapWithSpys.getNeighbors(currNode.currCity))
        {
            double neighborGScore = neighbor.second.first + currNode.g;

            if (shortestDistance.find(neighbor.first) == shortestDistance.end() || neighborGScore < shortestDistance[neighbor.first])
            {
                if (heuristic(currNode.currCity, neighbor.first) > spaceship->getControlLessDictance())
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
    if (spaceship->getControlLessDictance() >= distance)
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
            // std::cout << "enemy detect " << it->destination->getCoordinates().first << std::endl;
            it++;
            // continue;
        }
        else
        {
            it = AStarResults.erase(it);
        }
    }
    // std::cout << "size " << AStarResults.size() << std::endl;
    // for (auto res : AStarResults)
    // {
    //     std::cout << "in find " << res.destination->getCoordinates().first << " " << std::endl;
    // }
}

int Control::findAPathForARadarResistantSpaceship(const std::shared_ptr<Spaceship> &spaceship)
{
    std::sort(AStarResults.begin(), AStarResults.end(), compareTwoRoutsBasedOnSpys);

    for (int i = 0; i < AStarResults.size(); i++)
    {
        if (isSpaceshipRadarResistant(spaceship, AStarResults[i].numOfSpies))
            return i;
    }
    return -1;
}

AStarRes Control::findBestDestinationBasedOnDefenseRatio()
{
    std::sort(AStarResults.begin(), AStarResults.end(), compareTwoRoutsBasedOnDefenseRatio);

    return AStarResults[0];
}

/*int Control::findEnemyCity(const std::shared_ptr<City> &start, const std::shared_ptr<Spaceship> &spaceship)
{
    std::cout << spaceship->getRadarResistance() << " spaceship->getRadarResistance() in nfind enemy func " << std::endl;
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

    std::cout << "find enemy " << AStarResults.back().destination->getCoordinates().first << " " << AStarResults.back().destination->getCoordinates().second << std::endl;

    return chooseBestRoutSoFar(spaceship);
}
int Control::findBaseOrCivilCity(const std::shared_ptr<City> &start, const std::shared_ptr<Spaceship> &spaceship)
{
    std::cout << "in findBase or civil func spaceship->getRadarResistance() " << spaceship->getRadarResistance() << std::endl;
    if (spaceship->getRadarResistance() > 0)
    {
        std::cout << "to in if resistanceeeeeeeee\n";
        for (auto baseOrCivil : listOfBaseAndCivilCities)
        {
            if (baseOrCivil != start)
            {
                std::cout << "startttttttttt " << start->getCoordinates().first << " " << start->getCoordinates().second << std::endl;
                AStarResults.emplace_back(AStarRoutingForSpys(start, baseOrCivil, spaceship));
            }
        }
    }
    else
    {
        std::cout << "vard elseeeeeeeeeeeeeeeeeeeee\n";
        for (auto baseOrCivil : listOfBaseAndCivilCities)
        {
            if (baseOrCivil != start)
                AStarResults.emplace_back(AStarRoutingForDefenses(start, baseOrCivil, spaceship));
            if (bestRoutForEachSpaceship[spaceship].back().cost == -2)
                return -3; // out of both radar resistance and uncontrolled distance the spaceship is missed
        }
    }
    std::cout << bestRoutForEachSpaceship[spaceship].back().cost << " cost " << " des " << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().first
              << bestRoutForEachSpaceship[spaceship].back().destination->getCoordinates().second << " des "
              << bestRoutForEachSpaceship[spaceship].back().numOfObstacles << " obstacles " << std::endl;
    return chooseBestRoutSoFar(spaceship);
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
            std::cout << "manfi mishe " << rout.destination->getCoordinates().first << " " << rout.destination->getCoordinates().second << std::endl;
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
}*/
bool Control::compareTwoRoutsBasedOnSpys(const AStarRes &first, const AStarRes &second)
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
}
void Control::routing()
{
    for (auto spaceship : allSpaceships)
    {
        AStarRes finalResultForCurrentSpaceship;
        AStar(coordsToCityPtr[spaceship->getCoordinates()], allCities[allCities.size() - 1], spaceship);
        // for (auto r : AStarResults)
        // {
        //     std::cout << "destination " << r.destination->getCoordinates().first << " " << r.numOfSpies << " " << r.costOfPath << " " << std::endl;
        // }
        findValidReachedDestinations();
        int indexOfSelectedPath = findAPathForARadarResistantSpaceship(spaceship);
        if (indexOfSelectedPath == -1)
        {
            finalResultForCurrentSpaceship = findBestDestinationBasedOnDefenseRatio();
        }
        else
        {
            finalResultForCurrentSpaceship = AStarResults[indexOfSelectedPath];
        }
        std::cout << finalResultForCurrentSpaceship.destination->getCoordinates().first << "mmmmmmmmmm " << finalResultForCurrentSpaceship.numOfSpies << " "
                  << finalResultForCurrentSpaceship.costOfPath << std::endl;
    }
    // std::vector<std::shared_ptr<City>> finalRes = backtrackAStarPath(allCities[0], allCities[allCities.size() - 1]);
    // std::shared_ptr<City> startValidCity = nullptr, validDestinationCity = nullptr;

    // std::cout << trackNodes.size() << "trackNodes.size()" << std::endl;
    // for (auto um : trackNodes)
    // {
    //     std::cout << "track " << um.first->getCoordinates().first << " " << um.second->getCoordinates().first << std::endl;
    // }
    // std::cout <<"cost " <<a.costOfPath << " spy " << a.numOfSpies << std::endl;
    // while (1)
    // {
    //     for (auto um : trackNodes)
    //     {
    //         bool validRout = validateRoutBasedOnUncontrolledDistance(um.second, um.first, allSpaceships[0]);
    //         if (validRout)
    //         {

    //             startValidCity = um.second;
    //             validDestinationCity = um.first;
    //             break;
    //         }
    //     }

    //     if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(validDestinationCity))
    //         return;

    //     AStar(validDestinationCity, allCities[allCities.size() - 1], allSpaceships[0]);
    // }
    // for (auto f : finalRes)
    // {
    //     std::cout << f->getCoordinates().first << " finalRes" << std::endl;
    // }
    // for (auto &dis : shortestDistance)
    // {
    //     std::cout << "dis.first->getCoordinates().first " << dis.first->getCoordinates().first << " " << dis.first->getCoordinates().second << " " << dis.second << std::endl;
    // }

    // for (const auto &entry : AStarResultForEachCity)
    // {
    //     // std::shared_ptr<City> city = entry.first;
    //     const std::vector<AStarRes> &routes = entry.second;

    //     std::cout << "AStarResultForEachCity " << entry.first->getCoordinates().first << " ";
    //     // cout << "From City: " << city->name << endl;

    //     for (const auto &route : routes)
    //     {
    //         std::cout << "  - Distance: " << route.destination->getCoordinates().first << ", Cost: " << route.cost << std::endl;
    //     }
    // }
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
    // for (auto &a : eachCityHeuristics)
    // {

    //     std::cout << "huerstic " << a.first.first->getCoordinates().first << " " << a.first.second->getCoordinates().first << " " << a.second << std::endl;
    // }
}
int main()
{
    Control c;
    c.readMapFromFile();
    c.heuristicForAllCities();
    c.routing();
    // std::cout << "destruction " << c.amountOfDestruction << std::endl;
}