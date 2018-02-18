#pragma once
#include "game.h"
#include "terrain-navigator.h"
#include "generated\player-location_generated.h"

class PlayerLocationHandler                  // begin declaration of the class
{
public:                      // begin public section
	PlayerLocationHandler(TerrainNavigator, Game *);       // constructor
	PlayerLocationHandler(const PlayerLocationHandler& copy_from); //copy constructor
	~PlayerLocationHandler();                    // destructor
	void handle(const void *buf, Player &player);
private:                      // begin private section
	TerrainNavigator navigator_;
	Game *game_;
};