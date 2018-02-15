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

boost::asio::mutable_buffers_1 PlayerLocationHandler::handle(uint8_t *buf) {
	auto playerLocation = TransferObjects::GetPlayerLocation(buf);
	std::string idOut = playerLocation->id()->c_str();
	
	navigator_.Meow();
	
	std::cout << idOut << " to " << playerLocation->pos()->x() << ", " << playerLocation->pos()->y() << ", " << playerLocation->pos()->z();
	
	flatbuffers::FlatBufferBuilder fbb(1024);
	auto id = fbb.CreateString(playerLocation->id()->c_str());
	TransferObjects::PlayerLocationBuilder plb(fbb);
	plb.add_id(id);
	auto oldestPl = plb.Finish();
	//fbb.Finish(oldestPl);
	
	TransferObjects::FinishPlayerLocationBuffer(fbb, oldestPl);
	
	uint8_t * bufferPtr = fbb.GetBufferPointer();
	auto size = fbb.GetSize();

	return boost::asio::buffer(bufferPtr, size);
}

