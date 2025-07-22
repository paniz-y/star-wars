#ifndef CONTROL.HPP
#define CONTROL .HPP
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <cmath>
#include <fstream>
#include <iostream>
#include "Spaceship.hpp"
#include "City.hpp"
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
class Control : public Spaceship
{

public:
    void readMapFromFile();
    std::vector<int> AStarRouting(const std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> &map, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination); // uses A* search algorithm for routing

private:
    int scenario;
    int numOfCitys;
    int numOfBaseCitys;
    int numOfCivilCitys;
    int numOfEnemyCitys;
    std::vector<std::pair<int, int>> baseCityCoodinates;
    std::vector<std::pair<int, int>> civilCityCoodinates;
    std::vector<std::pair<int, int>> enemyCityCoodinates;
    std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> map;
};
#endif