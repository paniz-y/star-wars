#ifndef MAP_HPP
#define MAP_HPP
#include "City.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <memory>

class Map
{
public:
    std::vector<std::pair<std::shared_ptr<City>, double>> getNeighbors(std::shared_ptr<City> city);
    void addEdge(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex, double weight);
    
private:
    std::unordered_map<std::shared_ptr<City>, std::vector<std::pair<std::shared_ptr<City>, double>>> locationsGraph;
};
#endif
