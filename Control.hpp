#ifndef CONTROL_HPP
#define CONTROL_HPP
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "Spaceship.hpp"
#include "City.hpp"
#include "BaseCity.hpp"
#include "Map.hpp"
#include "EnemyCity.hpp"
#include "Defense.hpp"
struct Node
{
    std::shared_ptr<City> currCity;
    std::shared_ptr<City> prevCity;
    double g;
    double heuristic;
    double calculateF() const
    {
        return g + heuristic;
    }
    bool operator>(const Node &node) const
    {
        return calculateF() > node.calculateF();
    }
};
class Control
{

public:
    void readMapFromFile();
    void readBaseCitysFromFile();
    void readCivilCitysFromFile();
    void readEnemyCitysFromFile();
    void initializedBaseCities(std::vector<std::pair<int, int>> baseCityCoodinatesFromFile, std::vector<int> baseCitySpyFromFile);
    void initializeEnemyCities(std::vector<std::pair<int, int>> enemyCityCoodinatesFromFile, std::vector<int> enemyCitySpyFromFile, std::vector<Defense> enemyCitiesDefense);
    int CalculateDistance();
    void AStarRouting(Map map, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination); // uses A* search algorithm for routing

private:
    int scenario;
    int numOfCitys;
    int numOfBaseCitys;
    int numOfCivilCitys;
    int numOfEnemyCitys;
    std::fstream mapFile;
    Map map;
    // std::vector<std::pair<int, int>> baseCityCoodinates;
    // std::vector<std::pair<int, int>> civilCityCoodinates;
    // std::vector<std::pair<int, int>> enemyCityCoodinates;

    // std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> map;
};
#endif