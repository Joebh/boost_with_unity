#include <iostream>            // for cout and cin
#include "player-location.h"

// constructor of TerrainNavigator,
PlayerLocationHandler::PlayerLocationHandler(TerrainNavigator navigator) : navigator_(navigator)
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

void PlayerLocationHandler::handle(const void *buf) {
	auto playerLocation = TransferObjects::GetPlayerLocation(buf);
	std::string idOut = playerLocation->id()->c_str();
	
	//navigator_.getPath(playerLocation->pos()->x(), playerLocation->pos()->y(), playerLocation->pos()->z());

	std::cout << playerLocation->pos()->x() << " " << playerLocation->pos()->y();
	
	flatbuffers::FlatBufferBuilder fbb(1024);
	auto id = fbb.CreateString(playerLocation->id()->c_str());
	TransferObjects::PlayerLocationBuilder plb(fbb);
	plb.add_id(id);

	//plb.add_pos();
	
	auto oldestPl = plb.Finish();
	//fbb.Finish(oldestPl);
	
	TransferObjects::FinishPlayerLocationBuffer(fbb, oldestPl);
	
	uint8_t * bufferPtr = fbb.GetBufferPointer();
	auto size = fbb.GetSize();
}

