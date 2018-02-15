#include <iostream>            // for cout and cin

class TerrainNavigator                      // begin declaration of the class
{
public:                      // begin public section
	TerrainNavigator(std::string terrainFile);       // constructor
	TerrainNavigator(const TerrainNavigator& copy_from); //copy constructor
	TerrainNavigator& operator=(const TerrainNavigator& copy_from); //copy assignment
	~TerrainNavigator();                    // destructor

	void Meow();
private:                      // begin private section
	std::string terrainFile;
};

// constructor of TerrainNavigator,
TerrainNavigator::TerrainNavigator(std::string settingTerrainFile)
{
	terrainFile = settingTerrainFile;
}

//copy constructor for making a new copy of a TerrainNavigator
TerrainNavigator::TerrainNavigator(const TerrainNavigator& copy_from) {
	terrainFile = copy_from.terrainFile;
}

//copy assignment for assigning a value from one TerrainNavigator to another
TerrainNavigator& TerrainNavigator::operator=(const TerrainNavigator& copy_from) {
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
