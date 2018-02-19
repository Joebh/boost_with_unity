#include "player.h"
#include <iostream>

Player::Player(std::string username, unsigned __int64 clientId) :
	username_(username),
	serverClientId_(clientId),
	x_(0),
	y_(0),
	z_(0)
{
}

Player::~Player() 
{

}

void Player::setLocation(float x, float y, float z)
{
	x_ = float(x);
	y_ = float(y);
	z_ = float(z);
}

std::string Player::toBinary()
{
	flatbuffers::FlatBufferBuilder fbb(NetworkBufferSize);
	//auto id = fbb.CreateString(playerLocation->id()->c_str());

	TransferObjects::Vec3 destination(x_, y_, z_);
	TransferObjects::PlayerLocationBuilder plb(fbb);
	//plb.add_id(id);

	plb.add_dest(&destination);
		
	auto oldestPl = plb.Finish();
	//fbb.Finish(oldestPl);
	
	TransferObjects::FinishPlayerLocationBuffer(fbb, oldestPl);
	
	uint8_t * bufferPtr = fbb.GetBufferPointer();
	auto size = fbb.GetSize();

	return std::string(bufferPtr, bufferPtr + size);
}