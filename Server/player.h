#pragma once
#include <string>
#include "constants.h"
#include "flatbuffers\base.h"
#include "generated\player-location_generated.h"

class Player {
public:
	Player(std::string, unsigned __int64);
	~Player();

	void setLocation(float x, float y, float z);

	unsigned __int64 getClientId() { return serverClientId_; };

	std::string toBinary();

private:
	std::string username_;
	float x_, y_, z_;
	unsigned __int64 serverClientId_;
};