#include <iostream>            // for cout and cin
#include "player-handler.h"

// constructor of TerrainNavigator,
PlayerHandler::PlayerHandler(TerrainNavigator navigator, Game *game) : 
	navigator_(navigator),
	game_(game)
{
}

//copy constructor for making a new copy of a TerrainNavigator
PlayerHandler::PlayerHandler(const PlayerHandler& copy_from) 
	: navigator_(copy_from.navigator_) {
	
}

// destructor, just an example
PlayerHandler::~PlayerHandler()
{

}

void PlayerHandler::handle(const void *buf, Player *player) {
	auto playerData = TransferObjects::GetPlayer(buf);	
	player->setLocation(playerData->dest()->x(), playerData->dest()->y(), playerData->dest()->z());
}


std::string PlayerHandler::toBinary(Player *player)
{
	flatbuffers::FlatBufferBuilder fbb(NetworkBufferSize);
	//auto id = fbb.CreateString(playerLocation->id()->c_str());

	TransferObjects::Vec3 destination(player->getX(), player->getY(), player->getZ());
	TransferObjects::PlayerBuilder plb(fbb);
	//plb.add_id(id);

	plb.add_dest(&destination);

	auto oldestPl = plb.Finish();
	//fbb.Finish(oldestPl);

	TransferObjects::FinishPlayerBuffer(fbb, oldestPl);

	uint8_t * bufferPtr = fbb.GetBufferPointer();
	auto size = fbb.GetSize();

	return std::string(bufferPtr, bufferPtr + size);
}
