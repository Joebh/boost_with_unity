#pragma once
#include "game.h"
#include "generated\player-login_generated.h"

class PlayerLoginHandler                     // begin declaration of the class
{
public:                      // begin public section
	PlayerLoginHandler(Game *game);       // constructor
	PlayerLoginHandler(const PlayerLoginHandler& copy_from); //copy constructor
	~PlayerLoginHandler();                    // destructor
	void handle(const void *buf, unsigned __int64 serverClientId);
private:                      // begin private section
	Game *game_;
};