#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include <unordered_map>
#include <utility>
#include <memory>
#include "City.hpp"
#include "BaseCity.hpp"
#include "EnemyCity.hpp"

class Map
{
public:
    std::vector<std::pair<std::shared_ptr<City>, double>> getNeighbors(std::shared_ptr<City> city);
    void addEdge(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex, double weight);
    // void graphBaseCitys(std::vector<std::pair<int, int>> baseCityCoodinates, int baseCityNumOfSpys, std::vector<Spaceship> baseCitySpaceships);
    // std::vector<std::pair<std::shared_ptr<City>, double>> getNeighbors(std::shared_ptr<City> city);

    void graphMap(std::vector<std::shared_ptr<City>> cities);
    //void graphMapWithDefenses(std::vector<std::shared_ptr<City>> cities);

    int getMaxSize();
    void setMaxSize(int sizeOfMap);
    int calculateWeightForSpys(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex);     // calculates edge weights based on spys along the way
    //int calculateWeightForDefenses(std::shared_ptr<City> firstVertex, std::shared_ptr<City> secondVertex); // calculates edge weights based on defenses along the way
    //std::pair<double , double> pairWeightForSpysAndWeightForDefenses(double weightForSpys, double weightForDefenses);
    //void removeDefense(std::shared_ptr<City> firstVertex);
private:
    std::unordered_map<std::shared_ptr<City>, std::vector<std::pair<std::shared_ptr<City>, double>>> locationsGraph;
    int maxSize;
};
#endif
