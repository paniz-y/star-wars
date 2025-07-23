#include "Map.hpp"
std::vector<std::pair<std::shared_ptr<City>, double>> Map::getNeighbors(std::shared_ptr<City> city)
{
    return locationsGraph[city];
}
void Map::addEdge(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex, double weight)
{
    locationsGraph[firstVertex].emplace_back(secondVertex, weight);
    locationsGraph[secondVertex].emplace_back(firstVertex, weight);
}

void Map::graphBaseCitys(std::vector<std::pair<int, int>> baseCityCoodinates, int baseCityNumOfSpys, std::vector<Spaceship> baseCitySpaceships)
{
    for(int i = 0; i < baseCityCoodinates.size(); i++)
    {
        std::shared_ptr<BaseCity> base = std::make_shared<BaseCity> (baseCityCoodinates, baseCityNumOfSpys, baseCitySpaceships);
        
    }
}

// void Map::graphMap(std::vector<std::pair<int, int>> baseCityCoodinates, std::vector<std::pair<int, int>> civilCityCoodinates, std::vector<std::pair<int, int>> enemyCityCoodinates)
// {
    // for (int i = 0; i < baseCityCoodinates.size(); i++)
    // {
        
    //     addEdge(city)
    // }
//}
