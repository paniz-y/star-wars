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
    shortestDistance.clear();
    shortestDistance[start] = 0;
    for (auto &neighbor : mapWithSpies.getNeighbors(start))
    {
        shortestDistance[neighbor.first] = std::numeric_limits<double>::infinity();
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

PathResult AStar::hasReachedADestination(const Node &currNode, int spiesAtThePath, const std::shared_ptr<Spaceship> &spaceship)
{
    PathResult result = {currNode.currCity, spiesAtThePath, currNode.g};

    existingPathsForEachSpaceship[spaceship].emplace_back(result);
    pathResults.emplace_back(result);
    numOfSpiesForEachDestinationOfEachSpaceship[spaceship][result.destination] = result.numOfSpies;
    return result;
}

PathResult AStar::hasNotReachedDestination(const std::shared_ptr<City> &currCity, int spiesAtPath, const std::shared_ptr<Spaceship> &spaceship)
{
    PathResult result = {currCity, spiesAtPath, -1};
    existingPathsForEachSpaceship[spaceship].emplace_back(result);
    return result;
}
std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>> AStar::getExistingPathsForEachBaseCity()
{
    return existingPathsForEachBaseCity;
}

std::vector<std::shared_ptr<City>> AStar::backTrackToFindSpies(const std::shared_ptr<City> start, const std::shared_ptr<City> destination, int *spiesAtThePath)
{
    std::vector<std::shared_ptr<City>> path;
    std::shared_ptr<City> curr = destination;

    while (curr != nullptr)
    {
        path.push_back(curr); // add current city to path
        if (spiesAtThePath)
            *spiesAtThePath = increaseRadarResistant(curr, *spiesAtThePath);
        if (curr == start)
        {
            break;
        }

        curr = trackNodes.at(curr); // move to parent
    }
    if (spiesAtThePath)
        std::cout << "spies in back " << *spiesAtThePath << std::endl;
    std::reverse(path.begin(), path.end());
    return path;
}

PathResult AStar::AStarSearch(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship)
{
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node
    nodes.push({start, nullptr, 0, heuristic(start, destination)});

    initializeShortestDistanceForStart(mapWithSpies, start);

    int spiesAtThePath = 0;
    while (!nodes.empty())
    {
        Node currNode = nodes.top();
        nodes.pop();

        if (currNode.currCity == destination)
        {
            backTrackToFindSpies(start, destination, &spiesAtThePath);
            PathResult result = hasReachedADestination(currNode, spiesAtThePath, spaceship);
            existingPathsForEachBaseCity[start].emplace_back(result);
        }

        if (visitedNodeCities.find(currNode.currCity) != visitedNodeCities.end())
        {
            continue;
        }
        visitedNodeCities.insert(currNode.currCity);

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
                        backTrackToFindSpies(start, currNode.currCity, &spiesAtThePath);
                        PathResult result = hasReachedADestination(currNode, spiesAtThePath, spaceship);
                        spiesAtThePath = 0;
                        existingPathsForEachBaseCity[start].emplace_back(result);
                        continue; // for the current city there is no need to continue the rest of algorithm
                    }
                }

                shortestDistance[neighbor.first] = neighborGScore;
                if (neighbor.first->getCoordinates().second > currNode.currCity->getCoordinates().second)
                {
                    trackNodes[neighbor.first] = currNode.currCity;
                }

                double neighborHScore = heuristic(neighbor.first, destination);
                nodes.push({neighbor.first, currNode.currCity, neighborGScore, neighborGScore + neighborHScore});

                backTrackToFindSpies(start, currNode.currCity, &spiesAtThePath);
                PathResult result = hasReachedADestination(currNode, spiesAtThePath, spaceship);
                spiesAtThePath = 0;
                
                existingPathsForEachBaseCity[start].emplace_back(result);
            }
        }
    }

    PathResult result = hasNotReachedDestination(start, 0, spaceship);
    return result; // no rout found
}
std::vector<std::shared_ptr<City>> AStar::backtrackAStarPath(const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackedCities)
{
    std::vector<std::shared_ptr<City>> path;
    if (trackedCities.empty() || trackedCities.find(destination) == trackedCities.end())
    {
        throw std::runtime_error("Error: destination " + std::to_string(destination->getCoordinates().first) + " " + std::to_string(destination->getCoordinates().second) + " not found in trackedCities or trackedCities is empty.");
    }

    std::shared_ptr<City> current = destination;
    while (current != nullptr && current != start)
    {
        path.push_back(current);
        current = trackedCities.at(current);
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}