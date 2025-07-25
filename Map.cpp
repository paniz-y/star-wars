#include "Map.hpp"
std::vector<std::pair<std::shared_ptr<City>, double>> Map::getNeighbors(std::shared_ptr<City> city)
{
    return locationsGraph[city];
}
void Map::addEdge(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex, int weight)
{
    locationsGraph[firstVertex].emplace_back(secondVertex, weight);
    locationsGraph[secondVertex].emplace_back(firstVertex, weight);
}

// void Map::graphBaseCitys(std::vector<std::pair<int, int>> baseCityCoodinates, int baseCityNumOfSpys, std::vector<Spaceship> baseCitySpaceships)
// {
//     for (int i = 0; i < baseCityCoodinates.size(); i++)
//     {
//         std::shared_ptr<BaseCity> base = std::make_shared<BaseCity>(baseCityCoodinates[i], baseCityNumOfSpys, baseCitySpaceships);
//     }
// }

int Map::calculateWeight(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex)
{
    if(firstVertex->getExistenceOfSpy() || secondVertex->getExistenceOfSpy())
    {
        return maxSize * 2;
    }
    return 0;
}
void Map::graphMap(std::vector<std::shared_ptr<City>> cities)
{
    for (int i = 0; i < cities.size() - 1; i++)
    {
        for (int j = i + 1; j < cities.size(); j++)
        {
            addEdge(cities[i], cities[j], calculateWeight(cities[i], cities[j]));
        }
    }
}

