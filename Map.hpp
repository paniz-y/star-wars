#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include <unordered_map>
#include <utility>
#include <memory>
#include "City.hpp"
#include "BaseCity.hpp"

class Map
{
public:
    std::vector<std::pair<std::shared_ptr<City>, double>> getNeighbors(std::shared_ptr<City> city);
    void addEdge(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex, int weight);
    // void graphBaseCitys(std::vector<std::pair<int, int>> baseCityCoodinates, int baseCityNumOfSpys, std::vector<Spaceship> baseCitySpaceships);
    // std::vector<std::pair<std::shared_ptr<City>, double>> getNeighbors(std::shared_ptr<City> city); 
    
    void graphMap(std::vector<std::shared_ptr<City>> cities);
    int calculateWeight(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex); //calculates edge weights based on obstacles along the way

private:
    std::unordered_map<std::shared_ptr<City>, std::vector<std::pair<std::shared_ptr<City>, double>>> locationsGraph;
    int maxSize = 100;
};
#endif
