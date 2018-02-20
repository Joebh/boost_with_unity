#pragma once
#include "game.h"
#include "constants.h"
#include "flatbuffers\base.h"
#include "terrain-navigator.h"
#include "generated\player_generated.h"

class PlayerHandler                  // begin declaration of the class
{
public:                      // begin public section
	PlayerHandler(TerrainNavigator, Game *);       // constructor
	PlayerHandler(const PlayerHandler& copy_from); //copy constructor
	~PlayerHandler();                    // destructor
	void handle(const void *buf, Player *player);
	std::string PlayerHandler::toBinary(Player *player);
private:                      // begin private section
	TerrainNavigator navigator_;
	Game *game_;
};