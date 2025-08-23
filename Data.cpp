#include "Data.hpp"
void Data::readMapFromFile()
{
    mapFile.open("testcase8.txt", std::ios::in);
    if (!mapFile.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }
    readScenarioNumberFromFile();
    readBaseCitiesFromFile();
    readCivilCitiesFromFile();
    readEnemyCitiesFromFile();
    mapFile.close();
}
void Data::readMaxMapSizeFromFile()
{
    std::string maxOfMapString;
    mapFile >> maxOfMapString;
    mapFile >> maxMapSize;
}
void Data::readScenarioNumberFromFile()
{
    std::string scenarioString;
    mapFile >> scenarioString >> scenario;
}
void Data::readBaseCitiesFromFile()
{
    readNumberOfBasesFromFile();

    readBaseCoordinatesFromFile();

    readSpiesOfBaseCitiesFromFile();

    if (scenario == 7)
    {
        readMaxDamageFromFile();
    }
    else if (scenario != 3)
    {
        readSpaceshipsOfBasesFromFile();
    }
    else
    {
        readBaseCapacitesFromFile();
        readUnknownSpaceshipesFromFile();
    }
}
void Data::readNumberOfBasesFromFile()
{
    std::string numberOfBaseCitysFromFile;
    mapFile >> numberOfBaseCitysFromFile >> numOfBaseCities;
}
void Data::readMaxDamageFromFile()
{
    std::string maxDamageString;
    mapFile >> maxDamageString >> maxDamage;
}
void Data::readBaseCoordinatesFromFile()
{
    std::string baseCityCoordinatesFromFile;
    mapFile >> baseCityCoordinatesFromFile;

    baseCityCoodinatesFromFile.resize(numOfBaseCities); // resize the vector using achived number from file

    for (int i = 0; i < numOfBaseCities; i++)
    {
        mapFile >> baseCityCoodinatesFromFile[i].first >> baseCityCoodinatesFromFile[i].second;
    }
}
void Data::readSpiesOfBaseCitiesFromFile()
{
    std::string baseCitySpyStringFromFile;
    mapFile >> baseCitySpyStringFromFile;

    baseCitySpyFromFile.resize(numOfBaseCities);
    for (int i = 0; i < numOfBaseCities; i++)
    {
        mapFile >> baseCitySpyFromFile[i];
    }
}

void Data::readSpaceshipsOfBasesFromFile()
{
    std::string spaceshipString;
    mapFile >> spaceshipString;
    spaceshipsInBaseCities.resize(numOfBaseCities);
    std::string nameOfSPaceships, numberOfSpaceships;

    for (int i = 0; i < spaceshipsInBaseCities.size(); i++)
    {
        mapFile >> numberOfSpaceships >> spaceshipsInBaseCities[i].first;
        mapFile >> nameOfSPaceships;
        for (int j = 0; j < spaceshipsInBaseCities[i].first; j++)
        {
            std::string spaceshipTmpName;
            mapFile >> spaceshipTmpName;
            spaceshipsInBaseCities[i].second.emplace_back(spaceshipTmpName);
        }
    }
}
void Data::readBaseCapacitesFromFile()
{
    std::string basesCapacityStringFromFile;
    mapFile >> basesCapacityStringFromFile;

    basesCapacityFromFile.resize(numOfBaseCities);

    for (int i = 0; i < numOfBaseCities; i++)
    {
        mapFile >> basesCapacityFromFile[i];
    }
}
void Data::readUnknownSpaceshipesFromFile()
{
    std::string existingSpaceshipsString;
    mapFile >> existingSpaceshipsString;

    int totalNumberOfSpaceships = readTotalNumberOfUnknownSpaceshipsFromFile();

    spaceshipsToBeDivided.resize(totalNumberOfSpaceships);
    extractUnknownSpaceshipNamesFromFile(totalNumberOfSpaceships);
  
}

int Data::readTotalNumberOfUnknownSpaceshipsFromFile()
{
    std::string totalNumberString;
    int totalNumberOfSpaceships;
    mapFile >> totalNumberString >> totalNumberOfSpaceships;
    return totalNumberOfSpaceships;
}

std::vector<std::string> Data::extractUnknownSpaceshipNamesFromFile(int totalNumberOfSpaceships)
{
    std::string spaceshipsStringName;

    mapFile >> spaceshipsStringName;
    for (int i = 0; i < totalNumberOfSpaceships; i++)
    {
        mapFile >> spaceshipsToBeDivided[i];
    }
    return spaceshipsToBeDivided;
}

std::vector<int> Data::getBaseCitySpies() const
{
    return baseCitySpyFromFile;
}

std::vector<int> Data::getCivilCitySpies() const
{
    return civilCitySpyFromFile;
}

std::vector<int> Data::getEnemyCitySpies() const
{
    return enemyCitySpyFromFile;
}

std::vector<std::pair<int, int>> Data::getBaseCityCoodinates() const
{
    return baseCityCoodinatesFromFile;
}

std::vector<std::pair<int, int>> Data::getCivilCityCoodinates() const
{
    return civilCityCoodinatesFromFile;
}

std::vector<std::pair<int, int>> Data::getEnemyCityCoordinates() const
{
    return enemyCityCoordinatesFromFile;
}

std::vector<std::pair<int, std::vector<std::string>>> Data::getSpaceshipsInBaseCities() const
{
    return spaceshipsInBaseCities;
}

std::vector<int> Data::getBasesCapacity() const
{
    return basesCapacityFromFile;
}

std::vector<int> Data::getEnemyCityDefenseRatio() const
{
    return enemyCityDefenseRatioFromFile;
}

std::vector<std::string> Data::getSpaceshipsToBeDivided() const
{
    return spaceshipsToBeDivided;
}

std::vector<Defense> Data::getEnemyCitiesDefense() const
{
    return enemyCitiesDefense;
}

int Data::getMaxDamage() const
{
    return maxDamage;
}

int Data::getScenario() const
{
    return scenario;
}
int Data::getMaxMapSize() const
{
    return maxMapSize;
}
void Data::readCivilCitiesFromFile()
{
    readNumberOfCivilCitiesFromFile();
    readCivilCoordinatesFromFile();
    readCivilSpiesFromFile();
}
void Data::readNumberOfCivilCitiesFromFile()
{
    std::string numberOfCivilCitysFromFile;
    mapFile >> numberOfCivilCitysFromFile >> numOfCivilCities;
}
void Data::readCivilCoordinatesFromFile()
{
    civilCityCoodinatesFromFile.resize(numOfCivilCities);

    std::string civilCityCoordinatesFromFile;
    mapFile >> civilCityCoordinatesFromFile;

    for (int i = 0; i < numOfCivilCities; i++)
    {
        mapFile >> civilCityCoodinatesFromFile[i].first >> civilCityCoodinatesFromFile[i].second;
    }
}
void Data::readCivilSpiesFromFile()
{
    std::string civilCitySpyStringFromFile;
    mapFile >> civilCitySpyStringFromFile;

    civilCitySpyFromFile.resize(numOfCivilCities);
    for (int i = 0; i < numOfCivilCities; i++)
    {
        mapFile >> civilCitySpyFromFile[i];
    }
}
void Data::readEnemyCitiesFromFile()
{
    readNumberOfEnemyCitiesFromFile();
    readEnemyCoordinatesFromFile();
    readSpiesOfEnemyCitiesFromFile();
    readEnemyCitiesDefenseRatioFromFile();
    setEnemyCitiesDefenseFromFile();
}
void Data::readNumberOfEnemyCitiesFromFile()
{
    std::string numberOfEnemyCitysFromFile;
    mapFile >> numberOfEnemyCitysFromFile >> numOfEnemyCities;
}
void Data::readEnemyCoordinatesFromFile()
{
    std::string enemyCityCoordinatesStringFromFile;
    mapFile >> enemyCityCoordinatesStringFromFile;

    enemyCityCoordinatesFromFile.resize(numOfEnemyCities);
    for (int i = 0; i < numOfEnemyCities; i++)
    {
        mapFile >> enemyCityCoordinatesFromFile[i].first >> enemyCityCoordinatesFromFile[i].second;
    }
}
void Data::readSpiesOfEnemyCitiesFromFile()
{
    std::string enemyCitySpyStringFromFile;
    mapFile >> enemyCitySpyStringFromFile;

    enemyCitySpyFromFile.resize(numOfEnemyCities);
    for (int i = 0; i < numOfEnemyCities; i++)
    {
        mapFile >> enemyCitySpyFromFile[i];
    }
}
void Data::readEnemyCitiesDefenseRatioFromFile()
{
    std::string enemyCityDefenseStringRatioFromFile;
    mapFile >> enemyCityDefenseStringRatioFromFile;

    enemyCityDefenseRatioFromFile.resize(numOfEnemyCities);
    for (int i = 0; i < numOfEnemyCities; i++)
    {
        mapFile >> enemyCityDefenseRatioFromFile[i];
    }
}

void Data::setEnemyCitiesDefenseFromFile()
{
    enemyCitiesDefense.resize(numOfEnemyCities);
    for (int i = 0; i < numOfEnemyCities; i++)
    {
        enemyCitiesDefense[i].setRatio(enemyCityDefenseRatioFromFile[i]);
    }
}
