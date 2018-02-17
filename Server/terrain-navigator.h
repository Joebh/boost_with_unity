#pragma once
#include "DetourNavMesh.h"
#include "NavMeshSetHeader.h"

class TerrainNavigator                      // begin declaration of the class
{
public:                      // begin public section
	TerrainNavigator();       // constructor
	TerrainNavigator(const TerrainNavigator& copy_from); //copy constructor
	TerrainNavigator& operator=(const TerrainNavigator& copy_from); //copy assignment
	~TerrainNavigator();                    // destructor

	dtNavMesh* loadMesh(const char* path);
private:                      // begin private section
	std::string terrainFile;
};