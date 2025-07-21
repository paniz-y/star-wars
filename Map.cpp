#include "Map.hpp"
std::vector<std::pair<std::shared_ptr<City>, double>> Map::getNeighbors(std::shared_ptr<City> city)
{
    return locationsGraph[city];
}
void Map::addEdge(std::shared_ptr<City> a, std::shared_ptr<City> b, double weight)
{
    locationsGraph[a].emplace_back(b, weight);
    locationsGraph[b].emplace_back(a, weight);
}