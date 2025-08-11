#ifndef ASTAR_HPP
#define ASTAR_HPP
#include <queue>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <vector>
#include <float.h>
#include <optional>
#include "City.hpp"
#include "Spaceship.hpp"
#include "Map.hpp"

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
struct PathResult
{
    std::shared_ptr<City> destination;
    int numOfSpies; // stores the number of spies along the way
    double costOfPath;
    std::optional<int> maxPathLengthWithNoReprogram; // stores the maximum path length an spaceship must take without being reprogrammed
};
class AStar
{
public:
    std::vector<PathResult> getPathResults();
    int increaseRadarResistant(std::shared_ptr<City> city, int spaceshipRadarResistance);
    PathResult AStarSearch(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship);
    PathResult AStarSearchForUnKnownSpaceship(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination);
    std::vector<std::shared_ptr<City>> backtrackAStarPath(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination);
    double heuristic(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second); // calculates heuristic for A* search algorithm
    void initializeShortestDistanceForStart(Map mapWithSpies, const std::shared_ptr<City> &start);

private:
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodes; // stores each node and sortes them based on f score
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance;     // for each node stores the shortest distance required to reach it
    std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackNodes;
    std::vector<PathResult> pathResults; // stores all the valid path calculated with A* search algorithm
};
#endif