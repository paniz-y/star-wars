#include "Control.hpp"

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

    std::vector<std::shared_ptr<City>> baseCityForMap = initializeBaseCities(baseCityCoodinatesFromFile, baseCitySpyFromFile, spaceshipsInBaseCities);
    // for (int i = 0; i < numOfBaseCitys; i++)
    // {
    //     std::cout << numberOfSpaceships << " " << spaceshipsInBaseCities[i].first << " " << nameOfSPaceships << " " << spaceshipsInBaseCities[i].second << std::endl;
    // }
    // baseCityCoodinates.resize(numOfBaseCitys);
    // baseCityCoodinates = baseCityCoodinatesFromFile;
    return baseCityForMap;
}
std::vector<std::shared_ptr<Spaceship>> Control::findSuitableSpaceshipForBaseCities(std::vector<std::pair<int, std::string>> spaceshipsInBaseCities)
{
    std::vector<std::shared_ptr<Spaceship>> spaceshipFoundForBaseCity;
    for (int i{}; i < spaceshipsInBaseCities.size() && i < spaceshipsInBaseCities[i].first; i++)
    {
        spaceshipType type = stringToSpaceshipType(spaceshipsInBaseCities[i].second);
        switch (type)
        {
        case spaceshipType::Awing:
        {
            std::shared_ptr<Awing> tmpSpaceship = std::make_shared<Awing>();
            // allSpaceships.emplace_back(tmpSpaceship);
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            break;
        }
            // return std::make_shared<Awing>();
        case spaceshipType::DeathStar:
        {
            std::shared_ptr<DeathStar> tmpSpaceship = std::make_shared<DeathStar>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            // allSpaceships.emplace_back(tmpSpaceship);
            break;
        }
        case spaceshipType::Mantis:
        {
            std::shared_ptr<Mantis> tmpSpaceship = std::make_shared<Mantis>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            // allSpaceships.emplace_back(tmpSpaceship);
            break;
        }
        case spaceshipType::MillenniumFalcon:
        {
            std::shared_ptr<MillenniumFalcon> tmpSpaceship = std::make_shared<MillenniumFalcon>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            // allSpaceships.emplace_back(tmpSpaceship);
            break;
        }
        case spaceshipType::RazorCrest:
        {
            std::shared_ptr<RazorCrest> tmpSpaceship = std::make_shared<RazorCrest>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            // allSpaceships.emplace_back(tmpSpaceship);
            break;
        }
        case spaceshipType::StarDestroyer:
        {
            std::shared_ptr<StarDestroyer> tmpSpaceship = std::make_shared<StarDestroyer>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            // allSpaceships.emplace_back(tmpSpaceship);
            break;
        }
        case spaceshipType::TieFighter:
        {
            std::shared_ptr<TieFighter> tmpSpaceship = std::make_shared<TieFighter>();
            // allSpaceships.emplace_back(tmpSpaceship);
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            break;
        }
        case spaceshipType::XwingStarFighter:
        {
            std::shared_ptr<XwingStarFighter> tmpSpaceship = std::make_shared<XwingStarFighter>();
            spaceshipFoundForBaseCity.emplace_back(tmpSpaceship);
            // allSpaceships.emplace_back(tmpSpaceship);
            break;
        }
        default:
            throw std::invalid_argument("Unknown city type: " + spaceshipsInBaseCities[i].second);
        }
    }
    return spaceshipFoundForBaseCity;
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
        // auto coordsTmp = std::tie(enemyCityCoodinatesFromFile[i].first, enemyCityCoodinatesFromFile[i].second);
        coordsToCityPtr[enemyCityCoodinatesFromFile[i]] = enemyCities.back();
        // std::cout << " coordsToCityPtr[enemyCityCoodinatesFromFile[i]] "<< i << " " <<  coordsToCityPtr[enemyCityCoodinatesFromFile[i]]->getCoordinates().first << " " <<  coordsToCityPtr[enemyCityCoodinatesFromFile[i]]->getCoordinates().second << std::endl;
    }
    return enemyCities;
}
std::vector<std::shared_ptr<City>> Control::initializeBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile, std::vector<std::pair<int, std::string>> spaceshipsInBaseCities)
{
    std::vector<std::shared_ptr<City>> baseCities;
    for (int i = 0; i < baseCityCoodinatesFromFile.size(); i++)
    {
        std::vector<std::shared_ptr<Spaceship>> spaceshipsFoundFromBaseCities = findSuitableSpaceshipForBaseCities(spaceshipsInBaseCities);
        // std::cout << "spaceshipsFoundFromBaseCities size " << spaceshipsFoundFromBaseCities.size() << std::endl;
        std::shared_ptr<BaseCity> basePtrTmp = std::make_shared<BaseCity>(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i], spaceshipsFoundFromBaseCities);

        initializeAllSpaceships(spaceshipsFoundFromBaseCities, baseCityCoodinatesFromFile[i]);
        baseCities.emplace_back(basePtrTmp);
        // std::cout << "allSpaceship.size() " << i << " " << allSpaceships.size() << std::endl;
        // BaseCity baseCityTmp(baseCityCoodinatesFromFile[i], baseCitySpyFromFile[i], allSpaceships);
        // auto coordsTmp = std::tie(baseCityCoodinatesFromFile[i].first, baseCityCoodinatesFromFile[i].second);
        coordsToCityPtr[baseCityCoodinatesFromFile[i]] = baseCities.back();
        // std::cout <<" coordsToCityPtr[baseCityCoodinatesFromFile " << i << " " << coordsToCityPtr[baseCityCoodinatesFromFile[i]]->getCoordinates().first << " " << coordsToCityPtr[baseCityCoodinatesFromFile[i]]->getCoordinates().second << std::endl;
    }
    // std::cout << "allSpaceships size " << allSpaceships.size() << std::endl;
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
    mapFile.open("testcase2.txt", std::ios::in);
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
std::pair<int, int> Control::AStarRoutingForSpys(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship) // uses A* search algorithm for routing
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
    int radarResistanceTmp = spaceship->getRadarResistance();
    int radarResistanceSoFar = radarResistanceTmp;
    std::cout << "radarResistanceSoFar " << radarResistanceSoFar << std::endl;

    while (!nodes.empty())
    {

        Node currNode = nodes.top();
        nodes.pop();
        // std::cout << "previouseVisitedCity " << currNode.currCity->getCoordinates().first <<" " <<currNode.currCity->getCoordinates().second << std::endl;
        previouseVisitedCity = currNode.currCity;

        radarResistanceTmp = decreaseRadarResistant(currNode.currCity, radarResistanceTmp);
        radarResistanceSoFar = radarResistanceTmp;
        if (isSpaceshipRadarResistant(radarResistanceTmp))
        {
            if (currNode.currCity == destination)
            {
                // std::cout << "final " << currNode.g << std::endl;
                return std::make_pair(currNode.g, radarResistanceSoFar); // rout found
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
            return std::make_pair(-2, radarResistanceSoFar); // out of radar resitante
        }

        // std::cout << "after for \n";
    }
    return std::make_pair(-1, radarResistanceSoFar); // no rout wihtout exceeding controlless distance
}
int Control::AStarRoutingForDefenses(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship) // uses A* search algorithm for routing
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

    while (!nodes.empty())
    {
        Node currNode = nodes.top();
        nodes.pop();
        if (currNode.currCity == destination)
        {
            // std::cout << "final " << currNode.g << std::endl;
            return currNode.g;
        }

        // std::cout << "after if " << std::endl;
        if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(currNode.currCity)) // defense presence
        {
            // if (neighbor.second.second == mapWithDefenses.getMaxSize() * 2)
            // {
            //     jgkhgj
            // }
            int defenseRatioTmp = enemy->getDefense().getRatio();
            std::cout << "defenseRatioTmpppppppppppppppppppppppp " << defenseRatioTmp << std::endl;
            enemy->getDefense().defend();
            std::cout << "after defenddddddddddddd " << enemy->getDefense().getRatio() << std::endl;
            if (enemy->getDefense().getRatio() <= 0)
            {
                mapWithSpys.removeDefense(currNode.currCity);
            }
        }
        for (auto &neighbor : mapWithSpys.getNeighbors(currNode.currCity))
        {
            // std::cout << "currNode " << currNode.g << std::endl;
            double neighborGScore = neighbor.second.second + currNode.g;

            if ((visitedNodeCities.find(neighbor.first) == visitedNodeCities.end() || (neighborGScore < shortestDistance[neighbor.first]) && heuristic(start, destination) <= spaceship->getControlLessDictance()))
            {
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
    return -1; // no rout wihtout exceeding controlless distance
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
void Control::routing()
{
    initializeCorrespondentCityForEachSpaceship();
    for (auto spaceship : allSpaceships)
    {
        // std::cout << "befor for" << std::endl;
        for (auto enemy : listOfEnemyCities)
        {
            // std::cout << "before A star\n";
            // std::cout << "befor " << std::endl;
            // std::cout << "spaceship->getCoordinates()" << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
            // std::cout << "enemy.getCoordinates()" << enemy.getCoordinates().first << " " << enemy.getCoordinates().second << std::endl;
            // std::cout << "spaceship " << spaceship->getTypeOfSpaceship() << std::endl;
            routingResults.emplace_back(AStarRoutingForSpys(coordsToCityPtr[spaceship->getCoordinates()], coordsToCityPtr[enemy.getCoordinates()], spaceship));
            // std::cout << "A* for s first " << routingResults.back().first << std::endl;
            // std::cout << "A* for s second " << routingResults.back().second << std::endl;
            if (routingResults.back().first == -1) // exceeding the controlless distance
            {
                // std::cout << "here in if " << spaceship->getCoordinates().first << " " << spaceship->getCoordinates().second << std::endl;
                for (auto civilOrBase : listOfBaseAndCivilCities)
                {
                    // std::cout << "civil " <<
                    routingResults.emplace_back(AStarRoutingForSpys(previouseVisitedCity, civilOrBase, spaceship));
                }
            }
            if (routingResults.back().first == -2) //  out of radar resistant
            {
                // std::cout << "jooda " << std::endl;
                std::cout << "A* for d " << AStarRoutingForDefenses(previouseVisitedCity, coordsToCityPtr[enemy.getCoordinates()], spaceship) << std::endl;
            }
        }
    }
    for (auto res : routingResults)
    {
        std::cout << "res f " << res.first << " res s " << res.second << std::endl;
    }
}

bool Control::isSpaceshipRadarResistant(int spaceshipRadarResistance)
{
    bool isResistance = (spaceshipRadarResistance > 0) ? true : false;
    return isResistance;
}

int Control::decreaseRadarResistant(std::shared_ptr<City> city, int spaceshipRadarResistance)
{
    // int resistance = city->getExistenceOfSpy() ? (spaceshipRadarResistance--) : spaceshipRadarResistance;
    // return resistance;
    if (city->getExistenceOfSpy())
    {
        spaceshipRadarResistance--;
    }
    return spaceshipRadarResistance;
}

int main()
{
    Control c;
    c.readMapFromFile();
    c.routing();
}