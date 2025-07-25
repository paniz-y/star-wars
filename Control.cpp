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

    std::string baseCitySpyStringFromFile;
    std::vector <int> baseCitySpyFromFile;
    mapFile >> baseCitySpyStringFromFile;
    for (int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> baseCitySpyFromFile[i];
    }
    // baseCityCoodinates.resize(numOfBaseCitys);
    // baseCityCoodinates = baseCityCoodinatesFromFile;
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
    std::vector <int> civilCitySpyFromFile(numOfCivilCitys);
    mapFile >> civilCitySpyStringFromFile;
    for (int i = 0; i < numOfCivilCitys; i++)
    {
        mapFile >> civilCitySpyFromFile[i];
    }
    // civilCityCoodinates.resize(numOfCivilCitys);
    // civilCityCoodinates = civilCityCoodinatesFromFile;
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
    std::vector <int> enemyCitySpyFromFile(numOfEnemyCitys);
    mapFile >> enemyCitySpyStringFromFile;
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCitySpyFromFile[i];
    }

    std::string enemyCityDefenseStringRatioFromFile;
    mapFile >> enemyCityDefenseStringRatioFromFile;
    std::vector <int> enemyCityDefenseRatioFromFile(numOfEnemyCitys);
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        mapFile >> enemyCityDefenseRatioFromFile[i];
    }
    std::vector <Defense> enemyCitiesDefense;
    for (int i = 0; i < numOfEnemyCitys; i++)
    {
        enemyCitiesDefense[i].setRatio(enemyCityDefenseRatioFromFile[i]);
    }

    // enemyCityCoodinates.resize(numOfEnemyCitys);
    // enemyCityCoodinates = enemyCityCoodinatesFromFile;
}
void Control::initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile , std::vector <int> enemyCitySpyFromFile , std::vector <Defense> enemyCitiesDefense)
{
    std::vector <EnemyCity> enemyCities;
    for (int i = 0; i < enemyCityCoodinatesFromFile.size(); i++)
    {
        EnemyCity enemyTmp(enemyCityCoodinatesFromFile[i] , enemyCitySpyFromFile[i] , enemyCitiesDefense[i]);
        enemyCities.emplace_back(enemyTmp);
    }
}
// void Control::initializedBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile , std::vector <int> baseCitySpyFromFile)
// {
//     std::vector <BaseCity> baseCities;
//     for (int i = 0; i < baseCityCoodinatesFromFile.size(); i++)
//     {
//         BaseCity baseTmp(baseCityCoodinatesFromFile[i] , baseCitySpyFromFile[i] , baseCitySpyFromFile);
//         enemyCities.emplace_back(enemyTmp);
//     }
// }
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