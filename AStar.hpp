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
#include <iostream>
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
};
struct CompareNode
{
    bool operator()(const Node &a, const Node &b) const
    {
        return a.calculateF() > b.calculateF();
    }
};
struct PathResult
{
    std::shared_ptr<City> destination;
    int numOfSpies; // stores the number of spies along the way
    double costOfPath;
    std::optional<int> maxPathLengthWithNoReprogram; // stores the maximum path length an spaceship must take without being reprogrammed
    bool operator==(const PathResult &path)
    {
        if (path.destination == destination && path.numOfSpies == numOfSpies, path.costOfPath == costOfPath)
            return true;
        return false;
    }
};
class AStar
{
public:
    std::vector<PathResult> getPathResults();
    int increaseRadarResistant(std::shared_ptr<City> city, int spaceshipRadarResistance);
    void setTrackNodesForAstar(std::shared_ptr<City> neighbor , std::shared_ptr<City> curr);
    PathResult AStarSearch(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship);
    int backTrackToFindSpies(const std::shared_ptr<City> start, const std::shared_ptr<City> destination,std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackedCities);
    std::vector<std::shared_ptr<City>> backtrackAStarPath(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackedCities);
    double heuristic(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second); // calculates heuristic for A* search algorithm
    void initializeShortestDistanceForStart(Map mapWithSpies, const std::shared_ptr<City> &start);
    std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> getExistingPathsForEachSpaceship();
    std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> getTrackNodes();
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, int>> getNumOfSpiesForEachDestinationOfEachSpaceship();
    PathResult hasReachedADestination(const Node &currNode, int spiesAtThePath, const std::shared_ptr<Spaceship> &spaceship);
    PathResult hasNotReachedDestination(const std::shared_ptr<City> &currCity, int spiesAtThePath, const std::shared_ptr<Spaceship> &spaceship);
    std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>> getExistingPathsForEachBaseCity();
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>>> getExistingPathsForEachSpaceshipToEachDestination();

private:
    std::priority_queue<Node, std::vector<Node>, CompareNode> nodes;
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance; // for each node stores the shortest distance required to reach it
    std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackNodes;
    std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> existingPathsForEachSpaceship;
    ;                                    // stores all the valid path calculated with A* search algorithm for each spaceship
    std::vector<PathResult> pathResults; // stores all the valid path calculated with A* search algorithm
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, int>> numOfSpiesForEachDestinationOfEachSpaceship;
    std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>> existingPathsForEachBaseCity; // stores all the valid path calculated with A* search algorithm for each base city
    std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>>> existingPathsForEachSpaceshipToEachDestination;
};
#endif