#pragma once
#include <string>
#include "constants.h"
#include "flatbuffers\base.h"
#include "generated\player-location_generated.h"

class Player {
public:
	Player();
	Player(std::string);
	~Player();

	void setLocation(float x, float y, float z);

	std::string toBinary();

private:
	std::string username_;
	float x_, y_, z_;
};