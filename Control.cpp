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
    std::string baseCitySpysFromFile;
    int baseCityNumOfSpyFromFile;
    mapFile >> baseCitySpysFromFile;
    for(int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> baseCityNumOfSpyFromFile;
    }
    //baseCityCoodinates.resize(numOfBaseCitys);
    //baseCityCoodinates = baseCityCoodinatesFromFile;
    
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
    std::string civilCitySpysFromFile;
    int civilCityNumOfSpyFromFile;
    mapFile >> civilCitySpysFromFile;
    for(int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> civilCityNumOfSpyFromFile;
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
    std::string enemyCitySpysFromFile;
    int enemyCityNumOfSpyFromFile;
    mapFile >> enemyCitySpysFromFile;
    for(int i = 0; i < numOfBaseCitys; i++)
    {
        mapFile >> enemyCityNumOfSpyFromFile;
    }
    // enemyCityCoodinates.resize(numOfEnemyCitys);
    // enemyCityCoodinates = enemyCityCoodinatesFromFile;
}
// void Control::initializeCitys()
// {
//     // for (int i = 0; i < baseCityCoodinates.size(); i++)
//     // {
//     //     BaseCity base(baseCityCoodinates[i], )
//     // }
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
std::vector<int> Control::AStarRouting(const std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> &map, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination) // uses A* search algorithm for routing
{

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> previousNodes; // for each node stores the previous node that has been visited
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance;             // for each node stores the shortest distance required to reach it
    std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> neighbor;      // stores each node and its previous one for backtracking the path

    previousNodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
}
int main()
{
    Control c;
    c.readMapFromFile();
}