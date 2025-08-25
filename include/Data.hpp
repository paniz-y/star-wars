#ifndef DATA_HPP
#define DATA_HPP
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Spaceship.hpp"
#include "BaseCity.hpp"
#include "CivilCity.hpp"
#include "EnemyCity.hpp"
#include "Defense.hpp"

class Data
{
public:
    void readScenarioNumberFromFile();
    void readMapFromFile();
    void readMaxMapSizeFromFile();
    void readBaseCitiesFromFile();
    void readCivilCitiesFromFile();
    void readEnemyCitiesFromFile();
    void readNumberOfBasesFromFile();
    void readNumberOfCivilCitiesFromFile();
    void readNumberOfEnemyCitiesFromFile();
    void readMaxDamageFromFile();
    void readBaseCoordinatesFromFile();
    void readCivilCoordinatesFromFile();
    void readEnemyCoordinatesFromFile();
    void readCivilSpiesFromFile();
    void readSpiesOfBaseCitiesFromFile();
    void readSpiesOfEnemyCitiesFromFile();
    void readSpaceshipsOfBasesFromFile();
    void readBaseCapacitesFromFile();
    void readUnknownSpaceshipesFromFile();
    void readEnemyCitiesDefenseRatioFromFile();
    void setEnemyCitiesDefenseFromFile();
    void initializePriceFile();
    void readPricesFromFile();
    int readTotalNumberOfUnknownSpaceshipsFromFile();
    std::vector<std::string> extractUnknownSpaceshipNamesFromFile(int totalNumberOfSpaceships);
    std::vector<int> getBaseCitySpies() const;
    std::vector<int> getCivilCitySpies() const;
    std::vector<int> getEnemyCitySpies() const;
    std::vector<std::pair<int, int>> getBaseCityCoodinates() const;
    std::vector<std::pair<int, int>> getCivilCityCoodinates() const;
    std::vector<std::pair<int, int>> getEnemyCityCoordinates() const;
    std::vector<std::pair<int, std::vector<std::string>>> getSpaceshipsInBaseCities() const;
    std::vector<std::pair<std::string, int>> getSpaceshipPrices() const;
    std::vector<int> getBasesCapacity() const;
    std::vector<int> getEnemyCityDefenseRatio() const;
    std::vector<std::string> getSpaceshipsToBeDivided() const;
    std::vector<Defense> getEnemyCitiesDefense() const;
    int getMaxDamage() const;
    int getScenario() const;
    int getMaxMapSize() const;

private:
    int scenario;
    int numOfCitys;
    int numOfBaseCities;
    int numOfCivilCities;
    int numOfEnemyCities;
    int maxMapSize;
    int maxDamage; // uesd in 7'th scenario
    std::fstream mapFile;
    std::fstream priceFile;
    std::vector<std::shared_ptr<Spaceship>> allSpaceships;
    std::vector<std::pair<int, int>> baseCityCoodinatesFromFile;
    std::vector<std::pair<int, int>> civilCityCoodinatesFromFile;
    std::vector<std::pair<int, int>> enemyCityCoordinatesFromFile;
    std::vector<int> baseCitySpyFromFile;
    std::vector<int> civilCitySpyFromFile;
    std::vector<int> enemyCitySpyFromFile;
    std::vector<int> basesCapacityFromFile;
    std::vector<int> enemyCityDefenseRatioFromFile;
    std::vector<Defense> enemyCitiesDefense;
    std::vector<std::string> spaceshipsToBeDivided;
    std::vector<std::shared_ptr<EnemyCity>> listOfEnemyCities;
    std::vector<std::pair<std::string, int>> spaceshipPrices;
    std::vector<std::pair<int, std::vector<std::string>>> spaceshipsInBaseCities;
    std::vector<std::shared_ptr<City>> enemiesAsCity;
};
#endif