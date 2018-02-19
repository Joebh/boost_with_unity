#include <iostream>            // for cout and cin
#include "player-location.h"

// constructor of TerrainNavigator,
PlayerLocationHandler::PlayerLocationHandler(TerrainNavigator navigator, Game *game) : 
	navigator_(navigator),
	game_(game)
{
}

//copy constructor for making a new copy of a TerrainNavigator
PlayerLocationHandler::PlayerLocationHandler(const PlayerLocationHandler& copy_from) 
	: navigator_(copy_from.navigator_) {
	
}

// destructor, just an example
PlayerLocationHandler::~PlayerLocationHandler()
{

}

void PlayerLocationHandler::handle(const void *buf, Player *player) {
	auto playerLocation = TransferObjects::GetPlayerLocation(buf);	
	player->setLocation(playerLocation->dest()->x(), playerLocation->dest()->y(), playerLocation->dest()->z());
}

