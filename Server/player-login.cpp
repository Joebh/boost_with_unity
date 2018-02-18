#include <iostream>            // for cout and cin
#include "player-login.h"

// constructor of TerrainNavigator,
PlayerLoginHandler::PlayerLoginHandler(Game *game) :
	game_(game)
{
}

//copy constructor for making a new copy of a TerrainNavigator
PlayerLoginHandler::PlayerLoginHandler(const PlayerLoginHandler& copy_from) {

}

// destructor, just an example
PlayerLoginHandler::~PlayerLoginHandler()
{

}

void PlayerLoginHandler::handle(const void *buf, unsigned __int64 serverClientId) {
	auto playerLocation = TransferObjects::GetPlayerLogin(buf);
	std::string username = playerLocation->username()->c_str();
	std::string password = playerLocation->password()->c_str();

	// if valid id and pass

	// login
	game_->login(username, serverClientId);
}

