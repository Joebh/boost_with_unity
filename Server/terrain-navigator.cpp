#include <iostream>            // for cout and cin
#include "terrain-navigator.h"

// constructor of TerrainNavigator,
TerrainNavigator::TerrainNavigator(std::string settingTerrainFile)
{
	terrainFile = settingTerrainFile;
}

//copy constructor for making a new copy of a TerrainNavigator
TerrainNavigator::TerrainNavigator(const TerrainNavigator& copy_from) {
	terrainFile = copy_from.terrainFile;
}

// destructor, just an example
TerrainNavigator::~TerrainNavigator()
{

}

// definition of Meow method
// returns: void
// parameters: None
// action: Prints "meow" to screen
void TerrainNavigator::Meow()
{
	std::cout << "Meow.\n";
}
