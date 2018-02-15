#pragma once
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