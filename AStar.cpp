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
void AStar::setTrackNodesForAstar(std::shared_ptr<City> neighbor, std::shared_ptr<City> currCity)
{
    if (neighbor->getCoordinates().second > currCity->getCoordinates().second)
    {
        // std::cout << "inga to if tracknode" << std::endl;
        trackNodes[neighbor] = currCity;
    }
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
    // existingPathsForEachSpaceshipToEachDestination[spaceship][result.destination].emplace_back(result);
    pathResults.emplace_back(result);
    numOfSpiesForEachDestinationOfEachSpaceship[spaceship][result.destination] = result.numOfSpies;
    return result;
}

PathResult AStar::hasNotReachedDestination(const std::shared_ptr<City> &currCity, int spiesAtPath, const std::shared_ptr<Spaceship> &spaceship)
{
    PathResult result = {currCity, spiesAtPath, -1};
    existingPathsForEachSpaceship[spaceship].emplace_back(result);
    // existingPathsForEachSpaceshipToEachDestination[spaceship][result.destination].emplace_back(result);

    return result;
}
std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>> AStar::getExistingPathsForEachBaseCity()
{
    return existingPathsForEachBaseCity;
}

std::unordered_map<std::shared_ptr<Spaceship>, std::unordered_map<std::shared_ptr<City>, std::vector<PathResult>>> AStar::getExistingPathsForEachSpaceshipToEachDestination()
{
    return existingPathsForEachSpaceshipToEachDestination;
}

int AStar::backTrackToFindSpies(const std::shared_ptr<City> start, const std::shared_ptr<City> destination, std::unordered_map<std::shared_ptr<City>, std::shared_ptr<City>> trackedCities)
{
    std::vector<std::shared_ptr<City>> path;
    std::shared_ptr<City> curr = destination;
    int spiesAtThePath = 0;
    std::cout << "start " << start->getCoordinates().first << std::endl;
    std::cout << "des " << destination->getCoordinates().first << std::endl;
    for (auto &a : trackedCities)
        std::cout << "before " << a.first->getCoordinates().first << " " << a.second->getCoordinates().first << std::endl;
    // std::cout << trackNodes.size() << " size " << std::endl;
    if (trackedCities.empty() || trackedCities.find(destination) == trackedCities.end())
    {
        throw std::runtime_error("destination " + std::to_string(destination->getCoordinates().first) + " " + std::to_string(destination->getCoordinates().second) + " not found in trackedCities or trackedCities is empty.");
    }
    while (curr != nullptr && curr != start)
    {
        path.push_back(curr); // add current city to path
        spiesAtThePath = increaseRadarResistant(curr, spiesAtThePath);
        // if (curr == start)
        // {
        //     break;
        // }

        curr = trackedCities.at(curr); // move to parent
        // std::cout << "at " << curr->getCoordinates().first << std::endl;
    }
    spiesAtThePath = increaseRadarResistant(start, spiesAtThePath);
    for (auto &a : trackedCities)
        std::cout << "hi " << a.first->getCoordinates().first << " " << a.second->getCoordinates().first << std::endl;
    // std::cout << "kharge " << std::endl;
    // if (spiesAtThePath)
    std::cout << "spies in back " << spiesAtThePath << std::endl;
    // std::reverse(path.begin(), path.end());
    return spiesAtThePath;
}

PathResult AStar::AStarSearch(Map mapWithSpies, const std::shared_ptr<City> &start, const std::shared_ptr<City> &destination, std::shared_ptr<Spaceship> spaceship)
{
    std::unordered_set<std::shared_ptr<City>> visitedNodeCities; // stores each city that has been visited as a node

    nodes = std::priority_queue<Node, std::vector<Node>, CompareNode>(); // clear the nodes
    nodes.push({start, nullptr, 0, heuristic(start, destination)});
    // std::cout << "chejoori " << start->getCoordinates().first << std::endl;

    // if(spaceship->getCoordinates().first == 200)
    //     {while(!nodes.empty())
    // std::cout << "topolof " << nodes.top().currCity->getCoordinates().first << std::endl;
    // nodes.pop();}}
    initializeShortestDistanceForStart(mapWithSpies, start);

    int spiesAtThePath = 0;
    while (!nodes.empty())
    {
        // std::cout << "top " << nodes.top().currCity->getCoordinates().first << std::endl;
        // std::cout << "top " << nodes.top().currCity->getCoordinates().first << std::endl;
        Node currNode = nodes.top();
        nodes.pop();

        // std::cout << "cheraaaaaaaaa " << currNode.currCity->getCoordinates().first << std::endl;
        if (currNode.currCity == destination)
        {
            // std::cout << "to destiantion hastim " << currNode.currCity->getCoordinates().first << std::endl;
            // if (currNode.currCity->getCoordinates().second < destination->getCoordinates().second)
            //     backTrackToFindSpies(start, destination, &spiesAtThePath);
            PathResult result = hasReachedADestination(currNode, spiesAtThePath, spaceship);
            existingPathsForEachBaseCity[start].emplace_back(result);
            existingPathsForEachSpaceshipToEachDestination[spaceship][destination].emplace_back(result);
            return result;
        }

        if (visitedNodeCities.find(currNode.currCity) != visitedNodeCities.end())
        {
            continue;
        }
        visitedNodeCities.insert(currNode.currCity);

        // std::cout << "cuuuuuuuurrrr " << currNode.currCity->getCoordinates().first << std::endl;
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
                        // std::cout << "inja hastim " << std::endl;
                        // if (currNode.currCity != start && currNode.currCity->getCoordinates().first > start->getCoordinates().second)
                        //     backTrackToFindSpies(start, currNode.currCity, &spiesAtThePath);
                        PathResult result = hasReachedADestination(currNode, spiesAtThePath, spaceship);
                        spiesAtThePath = 0;
                        existingPathsForEachBaseCity[start].emplace_back(result);
                        continue; // for the current city there is no need to continue the rest of algorithm
                    }
                }

                shortestDistance[neighbor.first] = neighborGScore;

                double neighborHScore = heuristic(neighbor.first, destination);
                nodes.push({neighbor.first, currNode.currCity, neighborGScore, neighborGScore + neighborHScore});

                // std::cout << "dige " << std::endl;
                // if (currNode.currCity != start && currNode.currCity->getCoordinates().second > start->getCoordinates().second)
                //     backTrackToFindSpies(start, currNode.currCity, &spiesAtThePath);
                PathResult result = hasReachedADestination(currNode, spiesAtThePath, spaceship);
                // spiesAtThePath = 0;

                existingPathsForEachBaseCity[start].emplace_back(result);
                // if (currNode.currCity == start)
                // {
                //     setTrackNodesForAstar(neighbor.first, currNode.currCity);
                // }
                if (std::shared_ptr<BaseCity> base = std::dynamic_pointer_cast<BaseCity>(currNode.currCity))
                {
                    if (base != start)
                        continue;
                }
                std::cout << "naaaaaaaaaaa " << currNode.currCity->getCoordinates().second << " " << neighbor.first->getCoordinates().second << std::endl;
                // else if(currNode.currCity != start)
                    setTrackNodesForAstar(neighbor.first, currNode.currCity);
                // if (neighbor.first->getCoordinates().second > currNode.currCity->getCoordinates().second)
                // {
                //     std::cout << "inga to if tracknode" << std::endl;
                //     trackNodes[neighbor.first] = currNode.currCity;
                // }
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