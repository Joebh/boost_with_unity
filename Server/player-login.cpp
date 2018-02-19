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

std::string PlayerLoginHandler::handle(const void *buf, unsigned __int64 serverClientId) {
	auto playerLocation = TransferObjects::GetPlayerLogin(buf);
	std::string username = playerLocation->username()->c_str();
	std::string password = playerLocation->password()->c_str();

	// if valid id and pass

	// login
	game_->login(username, serverClientId);

	flatbuffers::FlatBufferBuilder fbb(NetworkBufferSize);
	TransferObjects::PlayerLoginBuilder plb(fbb);
	plb.add_success(true);
	auto successBuffer = plb.Finish();

	TransferObjects::FinishPlayerLoginBuffer(fbb, successBuffer);

	uint8_t * bufferPtr = fbb.GetBufferPointer();
	auto size = fbb.GetSize();

	return std::string(bufferPtr, bufferPtr + size);
}

