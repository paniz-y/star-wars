#include "Control.hpp"

std::vector<int> Control::AStarRouting(const std::unordered_map<std::shared_ptr<City>, std::pair<std::shared_ptr<City>, double>> &map, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination) // uses A* search algorithm for routing
{

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> previousNodes; // for each node stores the previous node that has been visited
    std::unordered_map<std::shared_ptr<City>, double> shortestDistance;             // for each node stores the shortest distance required to reach it
    std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> neighbor;          // stores each node and its previous one for backtracking the path

    previousNodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
}
double heuristic(const std::shared_ptr<City> &a, const std::shared_ptr<City> &b) // calculates heuristic for A* search algorithm
{
    std::pair<int, int> firstCityCoordinates = a->getCoordinates();
    std::pair<int, int> secondCityCoordinates = b->getCoordinates();
    double distance = sqrt(pow(firstCityCoordinates.first - secondCityCoordinates.first, 2) + pow(firstCityCoordinates.first - secondCityCoordinates.second, 2));
    return distance;
}
