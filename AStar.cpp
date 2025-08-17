#include "AStar.hpp"
std::vector<PathResult> AStar::getPathResults()
{
    return pathResults;
}

int AStar::increaseRadarResistant(std::shared_ptr<City> city, int spysDetected)
{
    if (city->getExistenceOfSpy())
    {
        spysDetected++;
    }
    return spysDetected;
}
double AStar::heuristic(const std::shared_ptr<City> &first, const std::shared_ptr<City> &second) // calculates heuristic for A* search algorithm
{
    std::pair<int, int> firstCityCoordinates = first->getCoordinates();
    std::pair<int, int> secondCityCoordinates = second->getCoordinates();
    double distance = sqrt(pow(firstCityCoordinates.first - secondCityCoordinates.first, 2) + pow(firstCityCoordinates.second - secondCityCoordinates.second, 2));
    return distance;
}

void AStar::initializeShortestDistanceForStart(Map mapWithSpies, const std::shared_ptr<City> &start)
{
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpies.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = DBL_MAX;
    }
}

std::unordered_map<std::shared_ptr<Spaceship>, std::vector<PathResult>> AStar::getExistingPathsForEachSpaceship()
{
    return existingPathsForEachSpaceship;
}

std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> AStar::getTrackNodes()
{
    return trackNodes;
}

std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, int>> AStar::getNumOfSpiesForEachDestinationOfEachSpaceship()
{
    return numOfSpiesForEachDestinationOfEachSpaceship;
}

// std::vector<std::vector<std::shared_ptr<City>>> AStar::validatePath(const std::shared_ptr<City> &start, const std::vector<std::shared_ptr<City>> &allEnemyCities)
// {
//     std::vector<std::vector<std::shared_ptr<City>>> completePathToEachDestination;
//     std::cout << " too backtrack1" << std::endl;

//     for (auto enemy : allEnemyCities)
//     {
//         std::vector<std::shared_ptr<City>> marg = backtrackAStarPath(start, enemy);
//         for (auto m : marg)
//         {
//             std::cout << m->getCoordinates().first << " marg" << std::endl;
//         }
//         completePathToEachDestination.emplace_back(backtrackAStarPath(start, enemy));
//     }
//     std::cout << " too backtrack3" << std::endl;

//     // for (auto first : completePathToEachDestination)
//     // {
//     //     std::cout << " too backtrack4" << std::endl;

//     //     for (auto second : first)
//     //     {
//     //     }
//     //     std::cout << std::endl;
//     // }
//     for (int i{}; i < completePathToEachDestination.size(); i++)
//     {
//         std::cout << " too backtrack4" << std::endl;

//         for (int j{}; j < completePathToEachDestination[i].size(); j++)
//         {
//             std::cout << " too backtrack5" << std::endl;

//             std::cout << completePathToEachDestination[i][j]->getCoordinates().first << " too backtrack";
//         }
//         std::cout << std::endl;
//     }
// }

PathResult AStar::AStarSearch(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship)
{
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node
    // trackNodes.clear();
    nodes.push({start, nullptr, 0, heuristic(start, destination)});

    // shortestDistance[start] = 0;
    // for (auto &neighbor : mapWithSpies.getNeighbors(start))
    // {
    //     shortestDistance[neighbor.first] = DBL_MAX;
    // }
    initializeShortestDistanceForStart(mapWithSpies, start);

    int spiesAtThePath = 0;
    while (!nodes.empty())
    {
        Node currNode = nodes.top();
        nodes.pop();

        if (currNode.currCity == destination)
        {
            spiesAtThePath = increaseRadarResistant(currNode.currCity, spiesAtThePath); // detecting whether the destination has spies
            PathResult result = {currNode.currCity, spiesAtThePath, currNode.g};

            existingPathsForEachSpaceship[spaceship].emplace_back(result);
            pathResults.emplace_back(result);
            numOfSpiesForEachDestinationOfEachSpaceship[spaceship][result.destination] = result.numOfSpies;
            return result;
        }

        if (visitedNodeCities.find(currNode.currCity) != visitedNodeCities.end())
        {
            continue;
        }
        visitedNodeCities.insert(currNode.currCity);

        spiesAtThePath = increaseRadarResistant(currNode.currCity, spiesAtThePath); // detecting whether the city has spies

        for (auto &neighbor : mapWithSpies.getNeighbors(currNode.currCity))
        {
            double neighborGScore = neighbor.second + currNode.g;

            if (shortestDistance.find(neighbor.first) == shortestDistance.end() || neighborGScore < shortestDistance[neighbor.first])
            {
                if (heuristic(currNode.currCity, neighbor.first) > spaceship->getUncontrolledDistance())
                {
                    continue; // reprogram the spaceship if required
                }
                if (std::shared_ptr<EnemyCity> enemy = std::dynamic_pointer_cast<EnemyCity>(currNode.currCity))
                {
                    if (std::shared_ptr<EnemyCity> neighborEnemy = std::dynamic_pointer_cast<EnemyCity>(neighbor.first))
                    {
                        PathResult result = {currNode.currCity, spiesAtThePath, currNode.g};
                        existingPathsForEachSpaceship[spaceship].emplace_back(result);
                        pathResults.emplace_back(result);
                        numOfSpiesForEachDestinationOfEachSpaceship[spaceship][result.destination] = result.numOfSpies;
                        continue; // for the current city there is no need to continue the rest of algorithm
                    }
                }

                shortestDistance[neighbor.first] = neighborGScore;
                trackNodes[neighbor.first] = currNode.currCity;

                double neighborHScore = heuristic(neighbor.first, destination);
                nodes.push({neighbor.first, currNode.currCity, neighborGScore, neighborGScore + neighborHScore});
                PathResult result = {currNode.currCity, spiesAtThePath, currNode.g};
                pathResults.emplace_back(result);
                numOfSpiesForEachDestinationOfEachSpaceship[spaceship][result.destination] = result.numOfSpies;
                existingPathsForEachSpaceship[spaceship].emplace_back(result);
            }
        }
    }
    PathResult result = {start, 0, -1};
    existingPathsForEachSpaceship[spaceship].emplace_back(result);
    return result; // no rout found
}
PathResult AStar::AStarSearchForUnKnownSpaceship(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, const std::shared_ptr<Spaceship> &spaceship)
{
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node

    nodes.push({start, nullptr, 0, heuristic(start, destination)});
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpies.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = DBL_MAX;
    }
    int spiesAtThePath = 0;
    int maxPathLength = 0;
    while (!nodes.empty())
    {
        Node currNode = nodes.top();
        nodes.pop();

        if (currNode.currCity == destination)
        {
            spiesAtThePath = increaseRadarResistant(currNode.currCity, spiesAtThePath); // detecting whether the destination has spies
            PathResult result = {currNode.currCity, spiesAtThePath, currNode.g, maxPathLength};
            pathResults.emplace_back(result);
            return result;
        }

        if (visitedNodeCities.find(currNode.currCity) != visitedNodeCities.end())
        {
            continue;
        }
        visitedNodeCities.insert(currNode.currCity);

        spiesAtThePath = increaseRadarResistant(currNode.currCity, spiesAtThePath); // detecting whether the city has spies

        for (auto &neighbor : mapWithSpies.getNeighbors(currNode.currCity))
        {
            double neighborGScore = neighbor.second + currNode.g;

            if (shortestDistance.find(neighbor.first) == shortestDistance.end() || neighborGScore < shortestDistance[neighbor.first])
            {
                if (heuristic(currNode.currCity, neighbor.first) > spaceship->getUncontrolledDistance())
                {
                    maxPathLength = 0;
                    continue; // reprogram the spaceship if required
                }
                if (heuristic(currNode.currCity, neighbor.first) > maxPathLength)
                {
                    maxPathLength = heuristic(currNode.currCity, neighbor.first); // checks for a longer path that must be taken without reprogramming
                }
                shortestDistance[neighbor.first] = neighborGScore;
                if (neighbor.first->getCoordinates().second > neighbor.first->getCoordinates().second)
                    trackNodes[neighbor.first] = currNode.currCity;

                double neighborHScore = heuristic(neighbor.first, destination);
                nodes.push({neighbor.first, currNode.currCity, neighborGScore, neighborGScore + neighborHScore});
                PathResult result = {currNode.currCity, spiesAtThePath, currNode.g, maxPathLength};
                pathResults.emplace_back(result);
            }
        }
    }
    PathResult result = {start, 0, -1, maxPathLength};
    return result; // no rout found
}

std::vector<std::shared_ptr<City>> AStar::backtrackAStarPath(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackedCities)
{
    std::vector<std::shared_ptr<City>> path;
    // std::cout << trackNodes.size() << " trackNodes.size()" << std::endl;
    // for (auto m : trackNodes)
    // {
    //     std::cout << m.first->getCoordinates().first << " " << m.second->getCoordinates().first << std::endl;
    // }
    // std::cout << destination << " m " << std::endl;
    if (trackedCities.empty() || trackedCities.find(destination) == trackedCities.end())
    {
        // std::cout << "empty" << std::endl;
        return {};
    }
    // std::cout << "bad empty" << std::endl;
    // std::cout << "start cheih " << start->getCoordinates().first << std::endl;
    std::shared_ptr<City> current = destination;
    while (current != nullptr && current != start)
    {
        path.push_back(current);
        // std::cout << "here " << trackedCities.at(current)->getCoordinates().first << std::endl;
        current = trackedCities.at(current);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    // for (auto m : trackNodes)
    // {
    //     std::cout << m.first->getCoordinates().first << " " << m.second->getCoordinates().first << std::endl;
    // }
    return path;
}