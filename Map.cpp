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

int Map::calculateWeightForSpys(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex)
{
    if (firstVertex->getExistenceOfSpy() && secondVertex->getExistenceOfSpy())
    {
        return maxSize * 4;
    }
    if (firstVertex->getExistenceOfSpy() || secondVertex->getExistenceOfSpy())
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
            double WeightForSpies = calculateWeightForSpys(cities[i], cities[j]);
            addEdge(cities[i], cities[j], WeightForSpies);
        }
    }
}

int Map::getMaxSize()
{
    return maxSize;
}

void Map::setMaxSize(int sizeOfMap)
{
    maxSize = sizeOfMap;
}
