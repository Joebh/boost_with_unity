#include "player.h"
#include <iostream>

Player::Player(std::string username, unsigned __int64 clientId) :
	username_(username),
	serverClientId_(clientId),
	x_(0),
	y_(0),
	z_(0),
	closePlayers_()
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