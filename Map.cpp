#include "Map.hpp"
std::vector<std::pair<std::shared_ptr<City>, std::pair<double, double>>> Map::getNeighbors(std::shared_ptr<City> city)
{
    return locationsGraph[city];
}
void Map::addEdge(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex, std::pair<double, double> weight)
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
int Map::calculateWeightForDefenses(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex)
{
    // if(firstVertex->getHasDefence() || secondVertex->getHasDefence())
    // {
    //     return maxSize * 2;
    // }
    if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(firstVertex))
    {
        return maxSize * 2;
    }
    if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(secondVertex))
    {
        return maxSize * 2;
    }
    return 0;
}

void Map::removeDefense(std::shared_ptr<City> firstVertex)
{
    for (auto neighbor : locationsGraph[firstVertex])
    {

       neighbor.second.second = 0;
    }
}

// std::pair<double, double> Map::pairWeightForSpysAndWeightForDefenses(double weightForSpys, double weightForDefenses)
// {
//     std::make_pair()
//     return std::pair<double, double>();
// }

void Map::graphMap(std::vector<std::shared_ptr<City>> cities)
{
    for (int i = 0; i < cities.size() - 1; i++)
    {
        for (int j = i + 1; j < cities.size(); j++)
        {
            std::pair<double, double> WeightForSpysAndWeightForDefenses = std::make_pair(calculateWeightForSpys(cities[i], cities[j]), calculateWeightForDefenses(cities[i], cities[j]));
            addEdge(cities[i], cities[j], WeightForSpysAndWeightForDefenses);
        }
    }
}
// void Map::graphMapWithDefenses(std::vector<std::shared_ptr<City>> cities)
// {
//     for (int i = 0; i < cities.size() - 1; i++)
//     {
//         for (int j = i + 1; j < cities.size(); j++)
//         {
//             addEdge(cities[i], cities[j], calculateWeightForDefenses(cities[i], cities[j]));
//         }
//     }
// }

int Map::getMaxSize()
{
    return maxSize;
}

void Map::setMaxSize(int sizeOfMap)
{
    maxSize = sizeOfMap;
}
